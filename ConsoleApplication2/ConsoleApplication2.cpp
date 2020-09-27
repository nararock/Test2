// ConsoleApplication2.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <vector>
#include <iterator>
using namespace std;
class Measurements {
private: 
    /// <summary>
    /// результаты вычислений СКО 
    /// </summary>
    float sigma_roll;
    float sigma_pitch;
    float sigma_course;
    vector <float> smooth_roll;// скользящие средние
    vector <float> smooth_pitch;
    vector <float> smooth_course;
public:
    Measurements(vector <float> roll, vector <float> pitch, vector <float> course) //входящие данные крен, тангаж и курс
    {
        sigma_roll = calculating_sigma(roll);
        sigma_pitch = calculating_sigma(pitch);
        sigma_course = calculating_sigma(course);
        smooth_roll = moving_average(roll); 
        smooth_pitch = moving_average(pitch);
        smooth_course = moving_average(course);
    };
    /// <summary>
    /// среднее арифметическое
    /// </summary>
    float calculating_mean(vector <float> :: iterator iter1, vector <float> ::iterator iter2) {
        float mean_vect = 0;
        int size = 0;
        for (; iter1 <= iter2; iter1++) {
            mean_vect += *iter1;
            size++;
        }
        mean_vect /= size;
        return mean_vect;
    }

    /// <summary>
    /// среднеквадратическое отклонение
    /// </summary>
    /// <param name="vect"></param>
    /// <returns></returns>
    float calculating_sigma(vector <float> vect) {
        if (vect.size() == 1)
            return 0;
        float mean_vect = calculating_mean(vect.begin(), vect.end() - 1);
        float variance = 0;
        for (int i = 0; i < vect.size(); i++) {
            variance += pow((vect.at(i) - mean_vect), 2);
        }
        variance /= (vect.size() - 1);
        float sigma = sqrt(variance);
        return sigma;
    }
    /// <summary>
    /// скользящее среднее
    /// </summary>
    vector <float> moving_average(vector <float> vect) {
        int window = 0;
        vector <float> smooth_var;
        cout << "Enter the size of the window\n";
        cin >> window;
        if (window > vect.size()) {
            cout << "The size of the window exceeds the size of the vector\n"
                << "The size of the vector is " << vect.size() << endl;
            return moving_average(vect);
        }
        else if (window == 0)
            return vect;
        else return calculating_moving_average(window, vect);
    }

    vector <float> calculating_moving_average(int window, vector <float> vect) {
        vector <float> result;
        for (int i = 0; i <= vect.size() - window; i++) {
            float mean = calculating_mean(vect.begin() + i, vect.begin() + i + window - 1);
            result.push_back(mean);
        }
        return result;
    }
};

int main()
{
    vector <float> example1 = {1, 2, 3, 4, 5, 6, 7, 8};
    vector <float> example2 = { -1, -2, -3, -4, 5, 6, 7, 8};
    vector <float> example3 = {0.1};
    Measurements m(example1, example2, example3);
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
