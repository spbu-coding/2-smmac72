// ставлю сотку, это заработает

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>

extern void sort(long long *pArray, int LEN);

int CheckArguments(int argc, char **argv, long long *FROM, long long *TO) {
    if (argc <= 1) // 0 аргументов
        return -1;
    if (argc > 3) // переизбыток аргументов
        return -2;

    const struct option long_options[] = {
            {"from", optional_argument, NULL, 'f'},
            {"to",   optional_argument, NULL, 't'},
            {NULL,   0,                 NULL, 0}
    };
    int option_index = 0;
    int firstExists = 0, secondExists = 0;
    opterr = 0;
    optind = 1;

    int result_of_reading = getopt_long(argc, argv, "", long_options, &option_index);

    while (result_of_reading != -1) {
        switch (result_of_reading) {
            case 'f':
                if (firstExists)
                    return -3;
                *FROM = strtoll((optarg ? optarg : "0"), NULL, 10);
                firstExists = 1;
                break;

            case 't':
                if (secondExists)
                    return -3;
                *TO = strtoll((optarg ? optarg : "0"), NULL, 10);
                secondExists = 1;
                break;

            default:
                return -4;
        }
        result_of_reading = getopt_long(argc, argv, "", long_options, &option_index);
    }
    if (!firstExists && !secondExists)
        return -4;
    if (!firstExists && secondExists)
        return 1;
    if (firstExists && !secondExists)
        return 2;
    return 0;
}

int main(int argc, char **argv)
{
    long long FROM, TO;
    int responseID = CheckArguments(argc, argv, &FROM, &TO);
    if (responseID < 0)
        return responseID;

    long long *array = malloc(sizeof(long long) * 100);
    if (!array)
    {
        printf("Unable to allocate sufficient memory");
        return -5;
    }
    char divider = ' ';
    unsigned initialElementsCount = 0;
    while (divider == ' ')
    {
        scanf("%lld%c", &array[initialElementsCount], &divider);
        initialElementsCount++;
    }

    size_t newSize = sizeof(long long) * initialElementsCount;
    long long *reducedArray = malloc(newSize);
    if (!reducedArray)
    {
        free(array);
        printf("Unable to allocate sufficient memory");
        return -5;
    }
    unsigned int LEN = 0;
    for (unsigned int i = 0; i < initialElementsCount; i++)
    {
        switch (responseID)
        {
            case 0:
                if (array[i] > FROM && array[i] < TO)
                {
                    reducedArray[LEN] = array[i];
                    LEN++;
                }
                if (array[i] <= FROM)
                    fprintf(stdout, "%lld ", array[i]);
                if (array[i] >= TO)
                    fprintf(stderr, "%lld ", array[i]);
                break;

            case 1:
                if (array[i] < TO)
                {
                    reducedArray[LEN] = array[i];
                    LEN++;
                }
                else if (array[i] >= TO)
                    fprintf(stderr, "%lld ", array[i]);
                break;

            case 2:
                if (array[i] > FROM)
                {
                    reducedArray[LEN] = array[i];
                    LEN++;
                }
                else if (array[i] <= FROM)
                    fprintf(stdout, "%lld ", array[i]);
                break;
        }
    }
    int changedPlaces = 0;
    if (LEN > 0)
    {
        long long *reducedCopy = malloc(newSize);
        if (!reducedCopy)
        {
            free(array);
            free(reducedArray);
            printf("Unable to allocate sufficient memory");
            return -5;
        }
        memcpy(reducedCopy, reducedArray, sizeof(long long) * LEN);
        sort(reducedArray, LEN);

        for (unsigned int i = 0; i < LEN; i++)
            if (reducedArray[i] != reducedCopy[i])
                changedPlaces++;

        free(reducedCopy);
    }
    free(array);
    free(reducedArray);
    return changedPlaces;
}
