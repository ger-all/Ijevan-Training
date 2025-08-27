#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

int main() {
    int n, k;
    cin >> n >> k;

    vector<int> numbers(n);
    for (int i = 0; i < n; ++i) {
        cin >> numbers[i];
    }

    // 1․ Հաշվել հաճախականությունը, օրինակը, 1-ից 2 հատ
    unordered_map<int, int> freq;
    for (int num : numbers) {
        freq[num]++;
    }

    // 2. Պահել map-ի զույգերը vector-ում (որպեսզի կարողանամ իմ ուզած ձևով sort անեմ)
    vector<pair<int, int>> v(freq.begin(), freq.end()); // pair<number, count>

    // 3. Sort անել,իջեցվող կարգով
    sort(v.begin(), v.end(), [](const auto& a, const auto& b) {
        return a.second > b.second;
        });

    // Քայլ 3: Տպել k ամենահաճախակի թիվը
    cout << "\nOutput:\n";
    for (int i = 0; i < k && i < (int)v.size(); ++i) {
        cout << v[i].first << " ";
    }
    cout << endl;

    return 0;
}

