#ifndef LOGGER_H
#define LOGGER_H

#define LOG_ERROR(format)                                                                          \
	fprintf(stderr, "ERROR: %s.%s:%d " format "\n", __FILE__, __func__, __LINE__);

#endif
