#include <iostream>
#include <ctime>
using namespace std;

int arr[100];
int arrBubble[100];
int arrLinearSearch[100];
int arrBinarySearch[100];
int arrMerge[100];
int arrQuick[100];
int arrSelection[100];
int arrInsertion[100];

double timeLinearSearch;
double timeBinarySearch;
double timeBubble;
double timeMerge;
double timeQuick;
double timeSelection;
double timeInsertion;

void printArray(int arr[], int n)
{
    for (int i = 0; i < n; ++i)
    {
        cout << arr[i] << " ";
    }
    cout << endl;
}
void printArray(int arr[], int n, const char *c)
{
    for (int i = 0; i < n; ++i)
    {
        cout << arr[i] << c;
    }
    cout << endl;
}
void delay(int ms)
{
    clock_t start_time = clock();
    while (clock() < start_time + ms * (CLOCKS_PER_SEC / 1000))
        ;
}
int linearSearch(int arr[], int n, int target)
{
    for (int i = 0; i < n; ++i)
    {
        cout << "Checking element at index " << i << ": " << arr[i] << endl;
        if (arr[i] == target)
            return i;
    }
    return -1;
}
int binarySearch(int arr[], int n, int target)
{
    int left = 0, right = n - 1;
    while (left <= right)
    {
        int mid = left + (right - left) / 2;
        cout << "Checking element at index " << mid << ": " << arr[mid] << endl;
        if (arr[mid] == target)
            return mid;
        else if (arr[mid] < target)
            left = mid + 1;
        else
            right = mid - 1;
    }
    return 1;
}
void bubbleSort(int arr[], int n)
{
    for (int i = 0; i < n - 1; ++i)
    {
        for (int j = 0; j < n - i - 1; ++j)
        {
            if (arr[j] > arr[j + 1])
            {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                printArray(arr, n);
            }
        }
    }
}
void selectionSort(int arr[], int n)
{
    for (int i = 0; i < n - 1; ++i)
    {
        int minIdx = i;
        for (int j = i + 1; j < n; ++j)
        {
            if (arr[j] < arr[minIdx])
                minIdx = j;
        }
        int temp = arr[i];
        arr[i] = arr[minIdx];
        arr[minIdx] = temp;
        printArray(arr, n);
    }
}
int partition(int arr[], int low, int high)
{
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; ++j)
    {
        if (arr[j] < pivot)
        {
            ++i;
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
            printArray(arr, high + 1);
        }
    }
    int temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;
    printArray(arr, high + 1);

    return i + 1;
}
void quickSort(int arr[], int low, int high)
{
    if (low < high)
    {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}
void quickSortWrapper(int arr[], int n)
{
    quickSort(arr, 0, n - 1);
}
void merge(int arr[], int left, int mid, int right)
{
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int L[n1], R[n2];

    for (int i = 0; i < n1; ++i)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; ++j)
        R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
            arr[k++] = L[i++];
        else
            arr[k++] = R[j++];
    }

    while (i < n1)
        arr[k++] = L[i++];
    while (j < n2)
        arr[k++] = R[j++];

    printArray(arr, right + 1);
}
void mergeSort(int arr[], int left, int right)
{
    if (left < right)
    {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}
void mergeSortWrapper(int arr[], int n)
{
    mergeSort(arr, 0, n - 1);
}

void insertionSort(int arr[], int n)
{
    for (int i = 1; i < n; ++i)
    {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            --j;
        }
        arr[j + 1] = key;
        printArray(arr, n);
    }
}
double measureSortingTime(void (*sortFunction)(int[], int), int arr[], int n, int algoId)
{
    clock_t start = clock();
    sortFunction(arr, n);
    clock_t end = clock();

    double timeTaken = double(end - start) / CLOCKS_PER_SEC;
    cout << "Time taken: " << timeTaken << " seconds" << endl;

    switch (algoId)
    {
    case 3:
        timeBubble = timeTaken;
        break;
    case 4:
        timeMerge = timeTaken;
        break;
    case 5:
        timeQuick = timeTaken;
        break;
    case 6:
        timeSelection = timeTaken;
        break;
    case 7:
        timeInsertion = timeTaken;
        break;
    }
    return 1;
}
void compareSortingAlgo(int algoId, int n)
{
    delay(1500);
    cout << "\n\n\n---- Comparison ----" << endl;
    if (algoId != 3)
    {
        delay(500);
        cout << "\n-- Bubble Sort Time: " << endl;
        cout << "original Array: " << endl;
        cout << " | ";
        for (int i = 0; i < n; i++)
        {
            cout << arrBubble[i] << " | ";
        }
        cout << "\n";
        for (int i = 0; i < n * 3; i++)
        {
            cout << "--";
        }
        cout << "\n";
        delay(500);
        measureSortingTime(bubbleSort, arrBubble, n, 3);
        cout << "\n----------------------------------------------\n";
    }
    if (algoId != 4)
    {
        delay(500);
        cout << "\n-- Merge Sort Time: " << endl;
        cout << "original Array: " << endl;
        cout << " | ";
        for (int i = 0; i < n; i++)
        {
            cout << arrMerge[i] << " | ";
        }
        cout << "\n";
        for (int i = 0; i < n * 3; i++)
        {
            cout << "--";
        }
        cout << "\n";
        delay(500);
        measureSortingTime(mergeSortWrapper, arrMerge, n, 4);
        cout << "\n----------------------------------------------\n";
    }
    if (algoId != 5)
    {
        delay(500);
        cout << "\n-- Quick Sort Time: " << endl;
        cout << "original Array: " << endl;
        cout << " | ";
        for (int i = 0; i < n; i++)
        {
            cout << arrQuick[i] << " | ";
        }
        cout << "\n";
        for (int i = 0; i < n * 3; i++)
        {
            cout << "--";
        }
        cout << "\n";
        delay(500);
        measureSortingTime(quickSortWrapper, arrQuick, n, 5);
        cout << "\n----------------------------------------------\n";
    }
    if (algoId != 6)
    {
        delay(500);
        cout << "\n-- Selection Sort Time: " << endl;
        cout << "original Array: " << endl;
        cout << " | ";
        for (int i = 0; i < n; i++)
        {
            cout << arrSelection[i] << " | ";
        }
        cout << "\n";
        for (int i = 0; i < n * 3; i++)
        {
            cout << "--";
        }
        cout << "\n";
        delay(500);
        measureSortingTime(selectionSort, arrSelection, n, 6);
        cout << "\n----------------------------------------------\n";
    }
    if (algoId != 7)
    {
        delay(500);
        cout << "\n-- Insertion Sort Time: " << endl;
        cout << "original Array: " << endl;
        cout << " | ";
        for (int i = 0; i < n; i++)
        {
            cout << arrInsertion[i] << " | ";
        }
        cout << "\n";
        for (int i = 0; i < n * 3; i++)
        {
            cout << "--";
        }
        cout << "\n";
        delay(500);
        measureSortingTime(insertionSort, arrInsertion, n, 7);
        cout << "\n----------------------------------------------\n";
    }

    delay(1500);
    cout << "\n\n\n-- Conclusion --" << endl;
    double timesOfAlgo[5] = {timeBubble, timeMerge, timeQuick, timeSelection, timeInsertion};
    double minValue = timesOfAlgo[0];
    int count = 0;

    for (int i = 0; i < 5; i++)
    {
        if (timesOfAlgo[i] < minValue)
        {
            minValue = timesOfAlgo[i];
            count = 1;
        }
        else if (timesOfAlgo[i] == minValue)
        {
            count++;
        }
    }

    cout << "\nEfficient Algorithm Count: " << count << endl;
    delay(20);
    cout << "\n-- Efficient Algorithm with Time: " << minValue << endl;
    for (int i = 0; i < 5; i++)
    {
        if (timesOfAlgo[i] == minValue)
        {
            cout << "   " << "* ";
            if (i == 0)
                cout << "Bubble Sort" << endl;
            else if (i == 1)
                cout << "Merge Sort" << endl;
            else if (i == 2)
                cout << "Quick Sort" << endl;
            else if (i == 3)
                cout << "Selection Sort" << endl;
            else if (i == 4)
                cout << "Insertion Sort" << endl;
        }
    }
}
void measureSearchingTime(int (*searchFunction)(int[], int, int), int arr[], int n, int target, int algoId)
{
    clock_t start = clock();
    int index = searchFunction(arr, n, target);
    clock_t end = clock();

    cout << "\n";
    double timeTaken = double(end - start) / CLOCKS_PER_SEC;
    cout << "\nTime taken: " << timeTaken << " seconds" << endl;

    if (index != -1)
    {
        delay(800);
        cout << "--------------------------------------";
        cout << "\nElement found at index " << index << endl;
        cout << "--------------------------------------\n";
    }
    else
    {
        delay(800);
        cout << "--------------------------------------";
        cout << "\nElement not found" << endl;
        cout << "--------------------------------------\n";
    }

    switch (algoId)
    {
    case 1:
        timeLinearSearch = timeTaken;
        break;
    case 2:
        timeBinarySearch = timeTaken;
        break;
    }
}
void compareSearchingAlgo(int algoId, int target, int n)
{
    delay(1500);
    cout << "\n\n\n---- Comparison ----" << endl;
    if (algoId != 1)
    {
        delay(500);
        cout << "\n-- Linear Search Time: " << endl;
        cout << "original Array: " << endl;
        cout << " | ";
        for (int i = 0; i < n; i++)
        {
            cout << arrLinearSearch[i] << " | ";
        }
        cout << "\n";
        for (int i = 0; i < n * 3; i++)
        {
            cout << "--";
        }
        cout << "\n";
        delay(500);
        measureSearchingTime(linearSearch, arrLinearSearch, n, target, 1);
    }
    if (algoId != 2)
    {
        delay(500);
        cout << "\n-- Binary Search Time: " << endl;
        cout << "original Array: " << endl;
        cout << " | ";
        for (int i = 0; i < n; i++)
        {
            cout << arrBinarySearch[i] << " | ";
        }
        cout << "\n";
        for (int i = 0; i < n * 3; i++)
        {
            cout << "--";
        }
        cout << "\n";
        quickSort(arrBinarySearch, 0, n - 1);
        cout << "\n";
        delay(500);
        measureSearchingTime(binarySearch, arrBinarySearch, n, target, 2);
    }

    delay(1500);
    cout << "\n\n-- Conclusion --" << endl;
    double minValue;
    int count = 0;
    if (timeLinearSearch < timeBinarySearch)
    {
        minValue = timeLinearSearch;
        count = 1;
    }
    else if (timeLinearSearch > timeBinarySearch)
    {
        minValue = timeBinarySearch;
        count = 1;
    }
    else if (timeLinearSearch == timeBinarySearch)
    {
        minValue = timeBinarySearch;
    }

    delay(200);
    cout << "\n-- Efficient Algorithm with Time: " << minValue << endl;
    if (minValue == timeLinearSearch)
    {
        cout << "   " << "* ";
        cout << "Linear Search" << endl;
    }
    else if (minValue == timeBinarySearch)
    {
        cout << "   " << "* ";
        cout << "Binary Search" << endl;
    }
    else
    {
        cout << "   " << "* ";
        cout << "Both are Efficient..." << endl;
    }
}
int main()
{
    char choice;
    do
    {
        cout << "\n------------------------------------\n";
        cout << "1. Linear Search\n2. Binary Search\n3. Bubble Sort\n";
        cout << "4. Merge Sort\n5. Quick Sort\n6. Selection Sort\n";
        cout << "7. Insertion Sort\n";
        cout << "------------------------------------\n";
        cout << "\n-- Select an Algorithm by entering its number: ";

        int algo_choice;
        cin >> algo_choice;

        cout << "\nEnter the number of elements: ";
        int n;
        cin >> n;

        cout << "Enter array elements separated by spaces:\n";
        cout << "--> ";
        for (int i = 0; i < n; i++)
        {
            cin >> arr[i];
        }
        for (int i = 0; i < n; i++)
        {
            arrBubble[i] = arr[i];
            arrLinearSearch[i] = arr[i];
            arrBinarySearch[i] = arr[i];
            arrMerge[i] = arr[i];
            arrQuick[i] = arr[i];
            arrSelection[i] = arr[i];
            arrInsertion[i] = arr[i];
        }
        switch (algo_choice)
        {
        case 1:
        {
            cout << "\n-- Selected Algorithm: Linear Search --\n";
            cout << "Enter target value: ";
            int target;
            cin >> target;
            cout << "| ";
            printArray(arr, n, " | ");
            cout << "\n";
            measureSearchingTime(linearSearch, arr, n, target, 1);
            delay(1000);
            compareSearchingAlgo(1, target, n);
            break;
        }
        case 2:
        {
            cout << "\n-- Selected Algorithm: Binary Search --\n";
            cout << "Enter target value: ";
            int target;
            cin >> target;
            cout << "| ";
            printArray(arr, n, " | ");
            cout << "\n";
            cout << "\n-- Sorting:\n";
            quickSort(arr, 0, n - 1);
            delay(500);
            cout << "\n-- Sorted Elements:\n";
            cout << "| ";
            printArray(arr, n, " | ");
            cout << "\n";
            measureSearchingTime(binarySearch, arr, n, target, 2);
            delay(1000);
            compareSearchingAlgo(2, target, n);
            break;
        }
        case 3:
            cout << "\n-- Selected Algorithm: Bubble Sort --\n";
            cout << "| ";
            printArray(arr, n, " | ");
            measureSortingTime(bubbleSort, arr, n, 3);
            delay(1000);
            cout << "\n-- Sorted Array:\n";
            cout << "| ";
            printArray(arr, n, " | ");
            compareSortingAlgo(3, n);
            break;
        case 4:
            cout << "\n-- Selected Algorithm: Merge Sort --\n";
            cout << "| ";
            printArray(arr, n, " | ");
            measureSortingTime(mergeSortWrapper, arr, n, 4);
            delay(1000);
            cout << "\n-- Sorted Array:\n";
            cout << "| ";
            printArray(arr, n, " | ");
            compareSortingAlgo(4, n);
            break;
        case 5:
            cout << "\n-- Selected Algorithm: Quick Sort --\n";
            cout << "| ";
            printArray(arr, n, " | ");
            measureSortingTime(quickSortWrapper, arr, n, 5);
            delay(1000);
            cout << "\n-- Sorted Array:\n";
            cout << "| ";
            printArray(arr, n, " | ");
            compareSortingAlgo(5, n);
            break;
        case 6:
            cout << "\n-- Selected Algorithm: Selection Sort --\n";
            cout << "| ";
            printArray(arr, n, " | ");
            measureSortingTime(selectionSort, arr, n, 6);
            delay(1000);
            cout << "\n-- Sorted Array:\n";
            cout << "| ";
            printArray(arr, n, " | ");
            compareSortingAlgo(6, n);
            break;
        case 7:
            cout << "\n-- Selected Algorithm: Insertion Sort --\n";
            cout << "| ";
            printArray(arr, n, " | ");
            measureSortingTime(insertionSort, arr, n, 7);
            delay(1000);
            cout << "\n-- Sorted Array:\n";
            cout << "| ";
            printArray(arr, n, " | ");
            compareSortingAlgo(7, n);
            break;
        default:
            cout << "Invalid choice" << endl;
        }
        cout << "\nWould you like to solve another problem? (y/n): ";
        cin >> choice;
    } while (choice == 'y' || choice == 'Y');

    cout << "Program ended.\n";
    return 0;
}
