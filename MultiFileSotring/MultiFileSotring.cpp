#include "MultiFileSotring.h"

void create_file(const string &name) {
    fstream temp(name, std::ios::out);
    temp.close();
}

void gen_rand_file(const string &name, int n) {
    create_file(name);
    fstream file(name);
    srand(time(nullptr));

    for(int i = 0;i < n - 1;i++) file << 1 + rand() % 100 << " ";
    file << 1 + rand() % 100;
    file.close();
}

std::pair<bool, int> isSortAndCount(const string &name) {
    fstream file(name);
    int counter = 0; bool isSorted = true;

    int prev, x; file >> prev;
    while(file >> x) {
        if(x == -1) break;
        counter++;
        if(x < prev) isSorted = false;
        prev = x;
    }

    file.close();
    return {isSorted, counter + 1};
}

vector<string> generate_file_names(int n) {
    vector<string> names(n);
    string sample = "Files" + string(1, char(92)) + "File";
    for(int i = 1;i <= n;i++){
        string number = std::to_string(i);
        names[i - 1] = (sample + number + ".txt");
    }
    return names;
}

void name(vector<string> &name, int n){
    string s1 = "data", s2, s3 = ".txt";

    for(int i = 0;i < n;i++){
        name.emplace_back(s1);
        s2 = std::to_string(i);
        name[i] += (s2 + s3);
    }
}

int Min(vector<int> &x, int n){
    int i, i_min, flag = 1, mini;

    for(i = 0;i < n && flag == 1; i++){
        if(x[i] != -1){
            mini = x[i];
            i_min = i;
            flag = 0;
        }
    }

    if(flag) return -1;

    for(;i < n;i++){
        if(x[i] < mini && x[i] != -1){
            mini = x[i];
            i_min = i;
        }
    }
    return i_min;
}

void divide(const string& input_file,vector<string> &names) {
    const int n = names.size() / 2;
    fstream* input = new fstream(input_file);

    fstream** out = new fstream*[n];
    for(int i = 0;i < n;i++) out[i] = new fstream(names[i]);

    int x, previous; *input >> x;
    *out[0] << x << " ";
    previous = x;
    int file_num = 0;

    while(!(input -> eof())){
        *input >> x;
        if(x < previous){
            *out[file_num % n] << -1 << " ";
            file_num++;
        }
        *out[file_num % n] << x << " ";
        previous = x;
    }
    *out[file_num % n] << -1 << " ";

    if(file_num < n)
        while(file_num != n)
            *out[file_num++] << -1 << " ";

    for(int i = 0;i < n;i++) {out[i] -> close();delete out[i];}
    delete [] out;
}

void merge(vector<string> &names){
    const int n = names.size() / 2;
    // Инициализация входных и выходных файлов
    fstream** out = new fstream*[2 * n];
    for(int i = 0;i < 2 * n;i++) out[i] = new fstream(names[i]);
    // Функция проверки, что есть не пустые файлы.
    auto isEnd = [&](){
        for(int i = 0;i < n;i++) if(!out[i] -> eof()) return true;
            return false;
    };

    int iterator;
    vector<int> x(n);
    // Читаем первый элемент из каждого файла
    for(int i = 0;i < n;i++)
        *out[i] >> x[i];
    // Инициализируем первый выходной файл.
    int file_num = n;
    bool allFiles = false;

    while(isEnd()){
        iterator = Min(x, n);

        if(iterator == -1) break;
        *out[file_num] << x[iterator] << " ";
        *out[iterator] >> x[iterator];
        // Если все -1, то надо переключится на следующий файл и считать начальный фрагмент
        bool flag = false;
        for(int& t : x)
            if(t != -1) flag = true;

        if(!flag){
            *out[file_num] << -1 << " ";
            file_num++;
            if(file_num >= names.size()){
                file_num = n;
                allFiles = true;
            }

            for(int i = 0;i < n;i++){
                int temp; *out[i] >> temp;
                if(out[i] -> eof()) x[i] = -1; // Если какой-то файл кончился, не беда просто на его месте будем писать -1
                else x[i] = temp;
            }
        }
    }
    // Дописываем в неиспользовнные файлы -1, чтобы сохранить инвариант.
    if(!allFiles)
        for(int i = file_num;i < 2*n;i++) *out[i] << -1 << " ";

    for(int i = 0;i < 2 * n;i++) {
        out[i] -> close();
        delete out[i];
    }
    delete [] out;
}