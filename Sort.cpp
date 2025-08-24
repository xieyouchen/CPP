#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>

using namespace std;

// ------------------ Bucket Sort ------------------
void bucketSort(std::vector<int>& arr) {
    int n = arr.size();
    if (n <= 0) return;
    int min_val = *std::min_element(arr.begin(), arr.end());
    int max_val = *std::max_element(arr.begin(), arr.end());
    int range = max_val - min_val + 1;
    
    // Create n buckets
    std::vector<std::vector<int>> buckets(n);
    
    // Distribute elements
    for (int num : arr) {
        int idx = (long long)(num - min_val) * (n - 1) / range;
        buckets[idx].push_back(num);
    }
    
    // Sort individual buckets and concatenate
    arr.clear();
    for (auto& bucket : buckets) {
        std::sort(bucket.begin(), bucket.end());
        arr.insert(arr.end(), bucket.begin(), bucket.end());
    }
}

// ------------------ Quick Sort ------------------
// int partition(std::vector<int>& arr, int low, int high) {
//     int pivot = arr[high];
//     int i = low - 1;
//     for (int j = low; j < high; ++j) {
//         if (arr[j] <= pivot) {
//             ++i;
//             std::swap(arr[i], arr[j]);
//         }
//     }
//     std::swap(arr[i + 1], arr[high]);
//     return i + 1;
// }

// void quickSort(std::vector<int>& arr, int low, int high) {
//     if (low < high) {
//         int pi = partition(arr, low, high);
//         quickSort(arr, low, pi - 1);
//         quickSort(arr, pi + 1, high);
//     }
// }

void quickSort(vector<int>& arr, int left, int right) {
    if(left < right) {
        int pivot = arr[right];
        int storeIndex = left;
        for(int i = left ; i < right ; i++) {
            if(arr[i] <= pivot) {
                swap(arr[storeIndex++], arr[i]);
            }
        }
        swap(arr[storeIndex], arr[right]);

        quickSort(arr, left, storeIndex-1);
        quickSort(arr, storeIndex+1, right);
    }
}

// ------------------ Merge Sort ------------------
void merge(std::vector<int>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    std::vector<int> L(n1), R(n2);
    std::copy(arr.begin() + left, arr.begin() + mid + 1, L.begin());
    std::copy(arr.begin() + mid + 1, arr.begin() + right + 1, R.begin());
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) arr[k++] = L[i++];
        else arr[k++] = R[j++];
    }
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
}

void mergeSort(std::vector<int>& arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

// ------------------ Testing Harness ------------------
int main() {
    const int SIZE = 20;
    std::vector<int> data(SIZE);

    // Generate random data
    std::mt19937 rng((unsigned)std::chrono::system_clock::now().time_since_epoch().count());
    std::uniform_int_distribution<int> dist(0, 99);
    for (int& v : data) v = dist(rng);

    // Prepare copies
    auto a = data;
    auto b = data;
    auto c = data;

    // Print original
    std::cout << "Original: ";
    for (int v : data) std::cout << v << ' ';
    std::cout << "\n";

    // Bucket Sort
    bucketSort(a);
    std::cout << "Bucket Sort: ";
    for (int v : a) std::cout << v << ' ';
    std::cout << "\n";

    // Quick Sort
    quickSort(b, 0, b.size() - 1);
    std::cout << "Quick Sort:  ";
    for (int v : b) std::cout << v << ' ';
    std::cout << "\n";

    // Merge Sort
    mergeSort(c, 0, c.size() - 1);
    std::cout << "Merge Sort:  ";
    for (int v : c) std::cout << v << ' ';
    std::cout << "\n";

    return 0;
}
