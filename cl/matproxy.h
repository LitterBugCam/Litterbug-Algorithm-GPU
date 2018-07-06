#ifndef MATPROXY_H
#define MATPROXY_H
#include <type_traits>
#include<opencv2/opencv.hpp>
#include <cassert>
//this class must keep type of stored values + translate Mat to aligned mat
//because on rpi GPU can process 16 values at once and we have 12 of such GPUs
//so can run 12 copies of processing by 16 numbers

template <typename T, int Aligment = 16 * 12>
class MatProxy
{
private:
    cv::Mat& source;
    std::vector<T> buffer;
    T FillBy;
public:
    //ensuring we use only plain types like float, int
    using value_type = typename std::enable_if<std::is_arithmetic<T>::value, T>::type;

    MatProxy(cv::Mat& source, T FillBy):
        source(source),
        FillBy(FillBy)
    {
        assert(source.cols * source.rows != 0);
        assert(source.type() == cv::DataType<T>::type);
    }

    MatProxy(cv::Mat& source, int rows, int cols):
        source(source)
    {
        source.create(rows, cols, cv::DataType<T>::type);
    }

    operator T*()
    {
        return ptr(true);
    }

    //returns memory which is multiply of aligment in size of elements
    T* ptr(bool copyMatrix = true)
    {
        assert(source.type() == cv::DataType<T>::type);
        const auto elements = source.cols * source.rows;
        const auto extra = elements % Aligment;
        if (extra)
        {
            const auto delta = Aligment - extra;

            const size_t sz = delta + elements;
            if (buffer.size() != sz)
                buffer.resize(delta + elements);

            if (copyMatrix)
            {
                memcpy(buffer.data(), source.ptr<T>(), sizeof(T) * elements);
                for (size_t i = elements; i < sz; ++i)
                    buffer[i] = FillBy;
            }

            return buffer.data();
        }
        return source.ptr<T>();
    }

    T* end()
    {
        return ptr(false) + sizeAligned();
    }

    int sizeAligned() const //in elements!
    {
        const auto elements = source.cols * source.rows;
        const auto extra = elements % Aligment;
        const auto delta = Aligment - extra;
        return delta + elements;
    }

    void updateMatrixIfNeeded()
    {
        assert(source.type() == cv::DataType<T>::type);
        const auto elements = source.cols * source.rows;
        const auto extra = elements % Aligment;
        if (extra > 0 && buffer.size() > static_cast<size_t>(extra))
            memcpy(source.ptr<T>(), buffer.data(), sizeof(T) * elements);
    }
};


#endif // MATPROXY_H
