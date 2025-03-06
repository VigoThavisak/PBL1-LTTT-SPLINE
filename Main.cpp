#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>
using namespace std;

struct Spline {
    double a, b, c, d, x;
};

void computeSpline(vector<double>& x, vector<double>& y, vector<Spline>& splines) {
    int n = x.size() - 1;
    vector<double> h(n), alpha(n), l(n + 1), mu(n + 1), z(n + 1);

    // Bước 1: Tính h[i] (độ dài từng đoạn)
    for (int i = 0; i < n; i++) h[i] = x[i + 1] - x[i];

    // Bước 2: Tính alpha[i]
    for (int i = 1; i < n; i++)
        alpha[i] = (3.0 / h[i]) * (y[i + 1] - y[i]) - (3.0 / h[i - 1]) * (y[i] - y[i - 1]);

    // Bước 3: Khởi tạo điều kiện biên
    l[0] = 1.0;
    mu[0] = 0.0;
    z[0] = 0.0;

    // Bước 4: Giải hệ phương trình tuyến tính để tìm c_i
    for (int i = 1; i < n; i++) {
        l[i] = 2.0 * (x[i + 1] - x[i - 1]) - h[i - 1] * mu[i - 1];
        mu[i] = h[i] / l[i];
        z[i] = (alpha[i] - h[i - 1] * z[i - 1]) / l[i];
    }

    // Điều kiện biên tự nhiên (c_n = 0)
    l[n] = 1.0;
    z[n] = 0.0;

    // Đảm bảo kích thước của vector `splines`
    splines.resize(n + 1);
    splines[n].c = 0.0; // Điều kiện biên

    // Bước 5: Tính toán các hệ số a, b, c, d
    for (int j = n - 1; j >= 0; j--) {
        splines[j].c = z[j] - mu[j] * splines[j + 1].c;
        splines[j].b = (y[j + 1] - y[j]) / h[j] - h[j] * (splines[j + 1].c + 2.0 * splines[j].c) / 3.0;
        splines[j].d = (splines[j + 1].c - splines[j].c) / (3.0 * h[j]);
        splines[j].a = y[j];
        splines[j].x = x[j];
    }
}

void drawGraph(vector<Spline>& splines, vector<double>& x, vector<double>& y) {
    ofstream output("output.txt", ios::app);
    cout << "\nGraph spline:\n";
    output << "\nGraph spline:\n";
    int width = 40, height = 15;
    char graph[height][width];


    for (int i = 0; i < height; i++)
        for (int j = 0; j < width; j++)
            graph[i][j] = ' ';

   
    int x_axis = height - 1; 
    int y_axis = 7;          

    for (int j = y_axis; j < width; j++) graph[x_axis][j] = '-'; 
    for (int i = 0; i < height; i++) graph[i][y_axis] = '|'; 
    graph[x_axis][y_axis] = '+'; 

    
    for (double xi = x[0]; xi <= x.back(); xi += (x.back() - x[0]) / width) {
        double yi;
        for (int i = 0; i < splines.size() - 1; i++) {
            if (xi >= splines[i].x && xi <= x[i + 1]) {
                double dx = xi - splines[i].x;
                yi = splines[i].a + splines[i].b * dx + splines[i].c * dx * dx + splines[i].d * dx * dx * dx;
                break;
            }
        }
        
        int plot_x = y_axis + 1 + (xi - x[0]) / (x.back() - x[0]) * (width - y_axis - 1);
        int plot_y = height - 1 - ((yi - y[0]) / (y.back() - y[0]) * (height - 1));
        
        if (plot_x >= y_axis + 1 && plot_x < width && plot_y >= 0 && plot_y < height)
            graph[plot_y][plot_x] = '*'; // ใส่จุด Spline ลงไป
    }

    // แสดงผลและบันทึกลงไฟล์
    for (int i = 0; i < height; i++) {
        if (i % 3 == 0) {
            cout << setw(7) << fixed << setprecision(2) << y.back() - ((y.back() - y[0]) / (height - 1)) * i << " | ";
            output << setw(7) << fixed << setprecision(2) << y.back() - ((y.back() - y[0]) / (height - 1)) * i << " | ";
        } else {
            cout << "        | ";
            output << "        | ";
        }
        
        for (int j = 0; j < width; j++) {
            cout << graph[i][j];
            output << graph[i][j];
        }
        cout << endl;
        output << endl;
    }

    // พิมพ์ตัวเลขที่แกน X
    cout << "        ";
    output << "        ";
    for (int j = y_axis + 5; j < width; j += width / 5) {
        cout << setw(7) << fixed << setprecision(1) << (x[0] + (x.back() - x[0]) * (j - y_axis) / (width - y_axis));
        output << setw(7) << fixed << setprecision(1) << (x[0] + (x.back() - x[0]) * (j - y_axis) / (width - y_axis));
    }
    cout << endl;
    output << endl;

    output.close();
}


int main() {
    vector<double> x, y;
    double temp_x, temp_y;
    int choice;
    cout << "--------------------------------DA NANG UNIVERSITY OF SCIENCE AND TECHNOLOGY------------------------------" << endl;
    cout << "------------------------------------DO AN LAP TRINH TINH TOAN-DE TAI 01-----------------------------------" << endl;
    cout << "-------------------------------------- SPLINE INTERPOLATION GRAPH ----------------------------------------" << endl;
    cout << "                                                                                                          " << endl;
    cout << "                                GIANG VIEN HUONG DAN : PGS.TS. NGUYEN TAN KHOI                            " << endl;
    cout << "                                                                                                          " << endl;
    cout << "                                                                                                          " << endl;
    cout << "-------NAME : SENTHAVISOUK THAVISAK                                   NAME : PHETCHAMPHONE HATSADY--------" << endl;
    cout << "--STUDENT CODE: 102230389                                                        STUDENT CODE: 102230390--" << endl;
    cout << "--CLASS: 23T-DT2                                                                          CLASS: 23T-DT2--" << endl;
    cout << endl;
    cout << "`                                       NAME : CHANSINA KHAMMALAY                                         " << endl;
    cout << "`                                       STUDENT CODE : 102240423                                          " << endl;
    cout << "`                                       CLASS : 24T_DT4                                                   " << endl;
    cout << endl;
    cout << "                      --------------------------------------------------------" << endl;
    cout << "Nhap 1 de nhap du lieu tu file" << endl;
    cout << "Nhap 2 de nhap du lieu bang tay" << endl;
    cout << "Lua chon cua ban: ";
    cin >> choice;
    
    if (choice == 1) {
        ifstream input("input.txt");
        while (input >> temp_x >> temp_y) {
            x.push_back(temp_x);
            y.push_back(temp_y);
        }
        input.close();
    } else {
        int n;
        cout << "Nhap so luong diem du lieu: ";
        cin >> n;
        ofstream outputFile("input.txt");
        cout << "Nhap cac cap gia tri x y:\n";
        for (int i = 0; i < n; i++) {
            cout << "Nhap x[" << i + 1 << "]: ";
            cin >> temp_x;
            cout << "Nhap y[" << i + 1 << "]: ";
            cin >> temp_y;
            x.push_back(temp_x);
            y.push_back(temp_y);
            outputFile << temp_x << " " << temp_y << endl;
        }
        outputFile.close();
    }
    
    int n = x.size() - 1;
    vector<Spline> splines(n + 1);
    
    computeSpline(x, y, splines);
    
    ofstream output("output.txt");
    cout << "Spline coefficients:" << endl;
    output << "Spline coefficients:" << endl;
    for (int i = 0; i < n; i++) {
        cout << "S[" << i << "]: " << fixed << setprecision(4) << splines[i].a << " "
             << splines[i].b << " " << splines[i].c << " " << splines[i].d << endl;
        output << "S[" << i << "]: " << fixed << setprecision(4) << splines[i].a << " "
               << splines[i].b << " " << splines[i].c << " " << splines[i].d << endl;
    }
    drawGraph(splines, x, y);
    system("\"C:\\gnuplot\\bin\\gnuplot.exe\" -p script.gnu");
    return 0;
}