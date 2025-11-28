/*
 * Copyright 2023 The Ungine Project Authors. All Rights Reserved.
 *
 * Licensed under the MIT (the "License").  You may not use
 * this file except in compliance with the License.  You can obtain a copy
 * in the file LICENSE in the source distribution or at
 * https://github.com/UngineOfficial/Ungine/blob/main/LICENSE
 */

/*────────────────────────────────────────────────────────────────────────────*/

#ifndef UNGINE_GPU_KERNEL
#define UNGINE_GPU_KERNEL

/*────────────────────────────────────────────────────────────────────────────*/

/* -- FRAGMENT_SHADERS -- */
namespace ungine { namespace kernel {

    string_t& fs_bds_material() { static string_t kernel = GPU_KERNEL(



    ); return kernel; }

} }

/*────────────────────────────────────────────────────────────────────────────*/

/* -- VERTEX_SHADERS -- */
namespace ungine { namespace kernel {

    string_t& vs_bds_material() { static string_t kernel = GPU_KERNEL(



    ); return kernel; }

} }

/*────────────────────────────────────────────────────────────────────────────*/

#endif

/*────────────────────────────────────────────────────────────────────────────*/
