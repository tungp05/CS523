#include <iostream>
#include <limits>
#include "QLSV.h"
using namespace std;

void menu() {
    cout << "\n===================== MENU =====================" << endl;
    cout << "1. Them sinh vien" << endl;
    cout << "2. Xoa sinh vien theo Ma SV" << endl;
    cout << "3. Tim sinh vien theo Ma SV" << endl;
    cout << "4. Tim sinh vien theo Ho ten" << endl;
    cout << "5. Hien thi bang du lieu va index hien tai" << endl;
    cout << "0. Thoat" << endl;
    cout << "================================================" << endl;
    cout << "Nhap lua chon: ";
}

int main() {
    QLSinhVien ql;
    ql.ThemSinhVien("SV003", "Nguyen Van A", "Nam", "12/03/2004", "Cong nghe thong tin");
    ql.ThemSinhVien("SV001", "Tran Thi B", "Nu", "25/07/2004", "He thong thong tin");
    ql.ThemSinhVien("SV005", "Le Van C", "Nam", "09/01/2003", "Ky thuat phan mem");
    ql.ThemSinhVien("SV002", "Pham Thi D", "Nu", "18/11/2004", "Khoa hoc may tinh");
    ql.ThemSinhVien("SV004", "Hoang Van E", "Nam", "30/05/2003", "Mang may tinh");

    int chon;

    do {
        menu();
        cin >> chon;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (chon) {
            case 1: {
                string MaSV, HoTen, GioiTinh, NgaySinh, NganhHoc;

                cout << "Nhap Ma SV: ";
                getline(cin, MaSV);

                cout << "Nhap Ho ten: ";
                getline(cin, HoTen);

                cout << "Nhap Gioi tinh: ";
                getline(cin, GioiTinh);

                cout << "Nhap Ngay sinh (dd/mm/yyyy): ";
                getline(cin, NgaySinh);

                cout << "Nhap Nganh hoc: ";
                getline(cin, NganhHoc);

                ql.ThemSinhVien(MaSV, HoTen, GioiTinh, NgaySinh, NganhHoc);
                break;
            }

            case 2: {
                string MaSV;
                cout << "Nhap Ma SV can xoa: ";
                getline(cin, MaSV);

                ql.XoaSinhVienTheoMa(MaSV);
                break;
            }

            case 3: {
                string MaSV;
                cout << "Nhap Ma SV can tim: ";
                getline(cin, MaSV);

                ql.TimTheoMa(MaSV);
                break;
            }

            case 4: {
                string HoTen;
                cout << "Nhap Ho ten can tim: ";
                getline(cin, HoTen);

                ql.TimTheoHoTen(HoTen);
                break;
            }

            case 5:
                ql.HienThiTatCa();
                break;

            case 0:
                cout << ">>> Ket thuc chuong trinh!" << endl;
                break;

            default:
                cout << ">>> Lua chon khong hop le!" << endl;
        }

    } while (chon != 0);

    return 0;
}
