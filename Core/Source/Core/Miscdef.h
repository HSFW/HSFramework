#pragma once

#define HS_BIT(x) (1 << (x))

#define HS_CONCAT_DETAIL(l, r) l##r
#define HS_STRINGIFY_DETAIL(x) #x

#define HS_CONCAT(l, r)      HS_CONCAT_DETAIL(l, r,)
#define HS_STRINGIFY(x)      HS_STRINGIFY_DETAIL(x)
