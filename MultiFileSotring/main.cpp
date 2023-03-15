#include "MultiFileSotring.h"

int main() {
    int n; cin >> n;
    vector<string> names; name(names, n);

    gen_rand_file("input.txt", 3000);
    for(int i = 0;i < n;i++)
        create_file(names[i]);
    // По названию понятно, делим входной файл на несколько.
    divide("input.txt", names);
    // Пока во втором файле не пусто, сливаем n входных в n выходных
    while(true){
        merge(names);
        //Проверка второго файла на пустоту
        fstream f(names[1]);
        int temp; f >> temp;
        f.close();
        if(temp == -1) break;
        //Чистка выходных файлов (не проверял, может она и не нужна)
        for(int i = 0;i < n / 2;i++){
            fstream basicFstream(names[i], std::ios::out);
            basicFstream.close();
        }
        // Смена входных и выходных файлов
        for(int i = 0;i < n / 2;i++){
            std::swap(names[i], names[i + n / 2]);
        }
    }

    std::pair<bool, int> ans = isSortAndCount(names[0]);
    cout << ((ans.first) ? "Yes " : "No ") << ans.second;
}