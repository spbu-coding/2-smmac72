#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
extern void InsertionSort(int *pArray, int LEN);

int CustomATOI(char *s, unsigned int LEN)
{
    int res = 0, minus = *s == '-';
    unsigned int counter = 0;
    if (minus)
    {
        s++;
        counter++;
    }

    while (isdigit(*s))
    {
        res = res*10 + (*s++ - '0');
        counter++;
    }
    if (counter != LEN)
    {
        return 0;
    }
    return minus ? -res : res;
}

int CheckArguments(int argc, char **argv, int *FROM, int *TO) {
    if (argc <= 1) // 0 аргументов
        return -1;
    if (argc > 3) // переизбыток аргументов
        return -2;
    if (argc == 3)
        if (strchr(argv[1], '=') == NULL && strchr(argv[2], '=') == NULL) // два "плохих" аргумента
            return -4;
    if (argc == 2 && strchr(argv[1], '=') == NULL)
        return -5; // кастомный ретурн. если один аргумент, и он "плохой"

    char *tmpFROM, *tmpTO;
    int changed = 0; // проверка на порядок --from и --to
    /////////////////////////////////////
    /// проверка префиксов аргументов ///
    /////////////////////////////////////

    int arg1LEN = 0, argLenFROM = 0, arg2LEN = 0, argLenTO = 0;
    int does1ArgExist = (strchr(argv[1], '=') != NULL ? 1 : 0); // бесполезно, на случай, если я для дебага уберу верхние проверки, и все умрет
    int does2ArgExist = (argc == 3 ? 1 : 0); // проверка наличия второго аргумента. вот это не убирать
    if (does2ArgExist)
        does2ArgExist = (strchr(argv[2], '=') != NULL ? 1 : 0);
    if (does1ArgExist)
    {
        arg1LEN = strlen(strchr(argv[1], '=')) - 1;
        argLenFROM = strlen(argv[1]) - arg1LEN;
        tmpFROM = malloc(sizeof(char) * (argLenFROM - 1));
        memcpy(tmpFROM, &argv[1][0], argLenFROM-1);
    }
    if (does2ArgExist)
    {
        arg2LEN = strlen(strchr(argv[2], '=')) - 1;
        argLenTO = strlen(argv[2]) - arg2LEN;
        tmpTO = malloc(sizeof(char) * (argLenTO-1));
        memcpy(tmpTO, &argv[2][0], argLenTO-1);
    }

    if (does1ArgExist && does2ArgExist)
    {
        if (strcmp(tmpFROM, tmpTO) == 0)
        {
            free(tmpFROM);
            free(tmpTO);
            return -3;
        }
        if (strstr(argv[1], "--from") == NULL || strstr(argv[2], "--to") == NULL)
        {
            if (strstr(argv[1], "--to") == NULL || strstr(argv[2], "--from") == NULL)
                return -4;
            else
                changed = 1;
        }
    }
    else if (does1ArgExist && !does2ArgExist)
    {
        if (strcmp(tmpFROM, "--to") == 0)
            changed = 1;
    }
    if (does1ArgExist)
        free(tmpFROM);
    if (does2ArgExist)
        free(tmpTO);



    /////////////////////////////////////
    //// проверка значений аргументов ///
    /////////////////////////////////////
    if (does1ArgExist) // проверка 1 аргумента. один аргумент есть точно, argc == 2 or argc == 3
    {
        tmpFROM = malloc(sizeof(char) * arg1LEN); // получение значения 1 аргумента
        memcpy(tmpFROM, &argv[1][argLenFROM], arg1LEN);
        if (changed)
            *TO = CustomATOI(tmpFROM, arg1LEN);
        else
            *FROM = CustomATOI(tmpFROM, arg1LEN);

    } else
        return 1; // кастомный ретурн. первый аргумент "плохой". значит второй точно будет "хорошим"
    if (does2ArgExist)
    {
        tmpTO = malloc(sizeof(char) * arg2LEN);
        memcpy(tmpTO, &argv[2][argLenTO], arg2LEN);
        if (changed)
            *FROM = CustomATOI(tmpTO, arg2LEN);
        else
            *TO = CustomATOI(tmpTO, arg2LEN);
    }
    else
        return 2; // второй аргумент "плохой", первый точно "хороший" согласно прошлым проверкам
    return 0;
}

int main(int argc, char **argv) {
    int FROM, TO;
    int responseID = CheckArguments(argc, argv, &FROM, &TO);
    if (responseID < 0)
        return responseID;

    int *array = malloc(sizeof(int) * 100);
    char divider = ' ';
    unsigned initialElementsCount = 0;
    while (divider == ' ') {
        scanf("%d%c", &array[initialElementsCount], &divider);
        initialElementsCount++;
    }

    size_t newSize = sizeof(int) * initialElementsCount;
    int *reducedArray = malloc(newSize);
    unsigned int LEN = 0;
    for (unsigned int i = 0; i < initialElementsCount; i++)
    {
        switch (responseID)
        {
            case 0:
                if (array[i] > FROM && array[i] < TO) {
                    reducedArray[LEN] = array[i];
                    LEN++;
                }
                else if (array[i] <= FROM)
                    fprintf(stdout, "%d ", array[i]);
                else
                    fprintf(stderr, "%d ", array[i]);
                break;

            case 1:
                if (array[i] < TO) {
                    reducedArray[LEN] = array[i];
                    LEN++;
                }
                else
                    fprintf(stderr, "%d ", array[i]);
                break;

            case 2:
                if (array[i] > FROM) {
                    reducedArray[LEN] = array[i];
                    LEN++;
                }
                else if (array[i] <= FROM)
                    fprintf(stdout, "%d ", array[i]);
                break;
        }
    }

    int *reducedCopy = malloc(newSize);
    memcpy(reducedCopy, reducedArray, sizeof(int) * LEN);
    InsertionSort(reducedArray, LEN);
    unsigned int changedPlaces = 0;
    for (unsigned int i = 0; i < LEN; i++)
        if (reducedArray[i] != reducedCopy[i])
            changedPlaces++;
    return changedPlaces;
}