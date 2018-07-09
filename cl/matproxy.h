#ifndef MATPROXY_H
#define MATPROXY_H
#include <type_traits>
#include<opencv2/opencv.hpp>
#include <cassert>
#include "../Litterheaders.h"

//this class must keep type of stored values + translate Mat to aligned mat
//because on rpi GPU can process 16 values at once and we have 12 of such GPUs
//so can run 12 copies of processing by 16 numbers

template <class IteratorA, class IteratorB>
void inline convert(const IteratorA start, const IteratorA end, IteratorB out)
{
    ALG_NS::transform(start, end, out, [](const typename std::iterator_traits<IteratorA>::value_type & a)
    {
        return static_cast<typename std::iterator_traits<IteratorB>::value_type>(a);
    });
}

template <typename T, typename KernelType = T>
class MatProxy
{
private:
    cv::Mat* source{nullptr};
    std::vector<KernelType> buffer;
    KernelType FillBy;
    const int Aligment;

    //returns memory which is multiply of aligment in size of elements
    KernelType* ptr(bool copyMatrix)
    {
        //std::cerr << source.type() << " " << cv::DataType<T>::type << "\n";
        assert(source->type() == cv::DataType<T>::type);
        const size_t elements = source->cols * source->rows;
        const auto extra = elements % Aligment;
        const auto delta = Aligment - extra;
        const size_t sz = delta + elements;

        if (std::is_same<T, KernelType>::value)
        {
            if (extra)
            {
                if (buffer.size() != sz)
                    buffer.resize(delta + elements);
                if (copyMatrix)
                {
                    memcpy(buffer.data(), source->ptr<T>(), sizeof(T) * elements);
                    for (size_t i = elements; i < sz; ++i)
                        *(buffer.data() + i) = FillBy;
                }

                return buffer.data();
            }
            return source->ptr<KernelType>(); //allowing compile, however cv::Mat should fail if KernekType != T
        }
        else
        {
            if (buffer.size() != sz)
                buffer.resize(delta + elements);

            if (copyMatrix)
            {
                convert(source->ptr<T>(), source->ptr<T>() + elements, buffer.data());
                for (size_t i = elements; i < sz; ++i)
                    *(buffer.data() + i) = FillBy;
            }
            return buffer.data();
        }
    }

public:
    //ensuring we use only plain types like float, int
    using value_type = typename std::enable_if<std::is_arithmetic<T>::value, T>::type;

    MatProxy(int Aligment = 16 * 12):
        Aligment(Aligment)
    {
    }

    MatProxy(cv::Mat& source, KernelType FillBy, int Aligment = 16 * 12):
        source(&source),
        FillBy(FillBy),
        Aligment(Aligment)
    {
        assert(source.cols * source.rows != 0);
        assert(source.type() == cv::DataType<T>::type);
    }

    MatProxy(cv::Mat& source, int rows, int cols, int Aligment = 16 * 12):
        source(&source),
        Aligment(Aligment)
    {
        source.create(rows, cols, cv::DataType<T>::type);
    }

    //allows to do statics
    void assign(cv::Mat& source, KernelType FillBy)
    {
        this->source = &source;
        this->FillBy = FillBy;
        assert(source.cols * source.rows != 0);
        assert(source.type() == cv::DataType<T>::type);
    }

    //allows to do statics
    void assign(cv::Mat& source, int rows, int cols)
    {
        if (source.rows != rows || source.cols != cols || source.type() != cv::DataType<T>::type)
            source.create(rows, cols, cv::DataType<T>::type);
        assert(source.cols * source.rows != 0);
        assert(source.type() == cv::DataType<T>::type);
        this->source = &source;
    }

    //copies source to temp buffer if needed
    KernelType* r_ptr()
    {
        return ptr(true);
    }

    //do not do copy, just returns pointer to buffer
    KernelType* w_ptr()
    {
        return ptr(false);
    }

    KernelType* end()
    {
        return w_ptr() + sizeAligned();
    }

    int sizeAligned() const //in elements!
    {
        const auto elements = source->cols * source->rows;
        const auto extra = elements % Aligment;
        if (extra)
        {
            const auto delta = Aligment - extra;
            return delta + elements;
        }
        return elements;
    }

    void updateMatrixIfNeeded()
    {
        assert(source->type() == cv::DataType<T>::type);
        const size_t elements = source->cols * source->rows;
        const auto extra = elements % Aligment;
        if (std::is_same<T, KernelType>::value)
        {
            if (extra > 0 && buffer.size() > static_cast<size_t>(extra))
                memcpy(source->ptr<T>(), buffer.data(), sizeof(T) * elements);
        }
        else
        {
            //this is damn slow...because we loosing aligment
            convert(buffer.data(), buffer.data() + elements, source->ptr<T>());
        }
    }
};


#endif // MATPROXY_H
