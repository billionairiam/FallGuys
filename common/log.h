#pragma once

#include "callbacks.h"

enum {
    LOG_LEVEL_NONE    =1,
    LOG_LEVEL_ERROR   =2,
    LOG_LEVEL_WARNING =3,
    LOG_LEVEL_DEBUG   =4,
    LOG_LEBEL_TRACE   =5,
    LOG_LEVEL_ALL     =6,
};

#define log_always(fmt...)  _log(LOG_LEVEL_NONE, fmt)
#define log_error(fmt...)  _log(LOG_LEVEL_ERROR, fmt)
#define log_warning(fmt...)  _log(LOG_LEVEL_WARNING, fmt)
#define log_debug(fmt...)  _log(LOG_LEVEL_DEBUG, fmt)
#define log_trace(fmt...)  _log(LOG_LEBEL_TRACE, fmt)