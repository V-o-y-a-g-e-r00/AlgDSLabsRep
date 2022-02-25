#ifndef SHELLSORT_INL_INCLUDED
#define SHELLSORT_INL_INCLUDED

void ShellSort(int *array, int size, bool SortOrder, bool IsStepbystep, int reclvl)
{
    for (int s = size / 2; s > 0; s /= 2) { //s - шаг в подсписке
        for (int i = s; i < size; ++i) { //каждая итерация - каждый подсписок
            for (int j = i - s; j >= 0 && array[j] > array[j + s]; j -= s) { //если перестановок не будет, то в этом подсписке для элементов с меньшими индексами в этом подсписке не нужно делать перестановку

                /*обмен между j и j+s*/
                int temp = array[j];
                array[j] = array[j + s];
                array[j + s] = temp;
            }
        }
        if (IsStepbystep)
        {   
            printArr<int>(array, size, std::string("After Step s=").append(std::to_string(s)).c_str(),0);
        }
    }
}

void shellsort1(int* l, int* r) {
	int sz = r - l;
	int step = sz / 2;
	while (step >= 1) {
		for (int *i = l + step; i < r; i++) {
			int *j = i;
			int *diff = j - step;
			while (diff >= l && *diff > *j) {
				std::swap(*diff, *j);
				j = diff;
				diff = j - step;
			}
		}
		step /= 2;
	}
}


#endif //SHELLSORT_INL_INCLUDED
