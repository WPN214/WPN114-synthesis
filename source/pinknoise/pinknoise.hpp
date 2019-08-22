#ifndef ASHES_H
#define ASHES_H

#include <wpn114audio/graph.hpp>

#define PINK_MAX_RANDOM_ROWS    (30)
#define PINK_RANDOM_BITS        (24)
#define PINK_RANDOM_SHIFT       ((sizeof(long)*8)-PINK_RANDOM_BITS)

//=================================================================================================
class Ashes : public Node
//=================================================================================================
{
    Q_OBJECT

    WPN_DECLARE_DEFAULT_AUDIO_OUTPUT (audio_out, 1)

    int64_t
    m_rows[PINK_MAX_RANDOM_ROWS];

    int64_t
    m_running_sum = 0;

    int32_t
    m_index = 0;

    int32_t
    m_index_mask = 0;

    float
    m_scalar = 0;

public:

    //---------------------------------------------------------------------------------------------
    Ashes()
    //---------------------------------------------------------------------------------------------
    {

    }

    //---------------------------------------------------------------------------------------------
    uint64_t
    draw()
    //---------------------------------------------------------------------------------------------
    {
        static uint64_t randseed = 22222;
        randseed = (randseed*19631465) + 907633515;
        return randseed;
    }

    //---------------------------------------------------------------------------------------------
    virtual void
    initialize(Graph::properties const& properties) override
    //---------------------------------------------------------------------------------------------
    {
        int32_t nrows = 16;
        m_index = 0;
        m_index_mask = (1 << nrows) - 1;
        int64_t pmax = (nrows+1) * (1 << PINK_RANDOM_BITS-1);
        m_scalar = 1.0f/pmax;

        for ( int i = 0; i < nrows; ++i )
              m_rows[i] = 0;
    }

    //---------------------------------------------------------------------------------------------
    virtual void
    rwrite(pool& inputs, pool& outputs, vector_t nframes) override
    //---------------------------------------------------------------------------------------------
    {
        auto out            = outputs.audio[0][0];
        auto index          = m_index;
        auto index_mask     = m_index_mask;
        auto rsum           = m_running_sum;
        auto scalar         = m_scalar;

        for (vector_t f = 0; f < nframes; ++f)
        {
            int64_t nrandom, sum;
            index = index+1 & index_mask;

            if (index)
            {
                int nzeros = 0;
                int n = index;

                while ((n & 1) == 0)
                {
                    n >>= 1;
                    nzeros++;
                }

                rsum -= m_rows[nzeros];
                nrandom = ((int64_t)draw())>> PINK_RANDOM_SHIFT;
                rsum += nrandom;
                m_rows[nzeros] = nrandom;
            }

            nrandom = ((int64_t)draw()) >> PINK_RANDOM_SHIFT;
            sum = rsum + nrandom;

            out[f] = scalar*sum;
        }

        m_index = index;
        m_running_sum = rsum;
    }
};

#endif // ASHES_H
