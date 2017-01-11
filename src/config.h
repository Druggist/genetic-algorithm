#ifndef CONFIG_H
#define CONFIG_H

static unsigned int _POPULATION_SIZE = 200;
static unsigned short _REMOVE_PCT = 50;
static unsigned short _REMOVE_FAIL_PCT = 7;
static unsigned short _MIN_RESECTION_PCT = 30;
static unsigned short _MAX_RESECTION_PCT = 100 - _MIN_RESECTION_PCT;
static unsigned short _MUTATION_CHANCE_PCT = 15;
static unsigned int _EXEC_TIME_SECS = 1 * 60;
#endif // CONFIG_H
