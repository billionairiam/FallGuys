#pragma once

#include <asm/stat.h>
#include <linux/time.h>
#include <linux/un.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdnoreturn.h>
#include <fcntl.h>
#include <asm/errno.h>
#include <string.h>
#include "syscall.h"

int read_text_file_to_cstr(const char* path, char** out)