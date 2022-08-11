#pragma once

#include <stddef.h>
#include <stdint.h>
#include <stdnoreturn.h>

/*
 * Output a formatted log message at a specific level (or drop it, if configured to do so).
 *
 * Used by `log_*` macros in `log.h`.
 */
void _log(int level, const char* fmt, ...) __attribute__((format(printf, 2, 3)));