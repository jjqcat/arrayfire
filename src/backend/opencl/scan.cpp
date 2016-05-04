/*******************************************************
 * Copyright (c) 2014, ArrayFire
 * All rights reserved.
 *
 * This file is distributed under 3-clause BSD license.
 * The complete license agreement can be obtained at:
 * http://arrayfire.com/licenses/BSD-3-Clause
 ********************************************************/

#include <af/dim4.hpp>
#include <Array.hpp>
#include <scan.hpp>
#include <complex>
#include <err_opencl.hpp>

#include <kernel/scan_first.hpp>
#include <kernel/scan_dim.hpp>

namespace opencl
{
    template<af_op_t op, typename Ti, typename To>
    Array<To> scan(const Array<Ti>& in, const int dim)
    {
        Array<To> out = createEmptyArray<To>(in.dims());

        try {
            Param Out = out;
            Param In  =   in;

            if (dim == 0)
                kernel::scan_first<Ti, To, op>(Out, In);
            else
                kernel::scan_dim  <Ti, To, op>(Out, In, dim);

        } catch (cl::Error &ex) {

            CL_TO_AF_ERROR(ex);
        }

        return out;
    }

#define INSTANTIATE(ROp, Ti, To)                                        \
    template Array<To> scan<ROp, Ti, To>(const Array<Ti>& in, const int dim); \

    //accum
    INSTANTIATE(af_add_t, float  , float  )
    INSTANTIATE(af_add_t, double , double )
    INSTANTIATE(af_add_t, cfloat , cfloat )
    INSTANTIATE(af_add_t, cdouble, cdouble)
    INSTANTIATE(af_add_t, int    , int    )
    INSTANTIATE(af_add_t, uint   , uint   )
    INSTANTIATE(af_add_t, intl   , intl   )
    INSTANTIATE(af_add_t, uintl  , uintl  )
    INSTANTIATE(af_add_t, char   , int    )
    INSTANTIATE(af_add_t, uchar  , uint   )
    INSTANTIATE(af_add_t, short  , int    )
    INSTANTIATE(af_add_t, ushort , uint   )
    INSTANTIATE(af_notzero_t, char  , uint)
}
