#ifndef QLSV_H
#define QLSV_H

#include <iostream>
#include <vector>
#include <iomanip>
#include "BTree.h"
using namespace std;

struct SinhVien {
    string MaSV;
    string HoTen;
    string GioiTinh;
    string NgaySinh;
    string NganhHoc;
    bool deleted;
};

class QLSinhVien {
private:
    vector<SinhVien> BangGoc;
    BTree IndexMaSV;
    BTree IndexHoTen;

    void RebuildIndex() {
        IndexMaSV.Reset();
        IndexHoTen.Reset();

        for (int i = 0; i < (int)BangGoc.size(); i++) {
            if (!BangGoc[i].deleted) {
                IndexMaSV.insert(BangGoc[i].MaSV, i);
                IndexHoTen.insert(BangGoc[i].HoTen, i);
            }
        }
    }

public:
    void HienThiBangGoc() {
        cout << "\n==================== BANG DU LIEU GOC ====================" << endl;
        cout << left
             << setw(5)  << "STT"
             << setw(10) << "MaSV"
             << setw(25) << "Ho ten"
             << setw(10) << "Gioi Tinh"
             << setw(15) << "Ngay sinh"
             << setw(20) << "Nganh hoc"
             << setw(10) << "TrangThai"
             << endl;
        cout << "--------------------------------------------------------------------------" << endl;

        if (BangGoc.empty()) {
            cout << "(Chua co du lieu)" << endl;
            return;
        }

        for (int i = 0; i < (int)BangGoc.size(); i++) {
            cout << left
                 << setw(5)  << i
                 << setw(10) << BangGoc[i].MaSV
                 << setw(25) << BangGoc[i].HoTen
                 << setw(10) << BangGoc[i].GioiTinh
                 << setw(15) << BangGoc[i].NgaySinh
                 << setw(20) << BangGoc[i].NganhHoc
                 << setw(10) << (BangGoc[i].deleted ? "Da xoa" : "Ton tai")
                 << endl;
        }
    }

    void HienThiIndex() {
        cout << "\n==================== INDEX THEO MA SV ====================" << endl;
        IndexMaSV.Print();
        cout << "\n==================== INDEX THEO HO TEN ====================" << endl;
        IndexHoTen.Print();
    }

    void HienThiTatCa() {
        HienThiBangGoc();
        HienThiIndex();
    }

    void ThemSinhVien(string MaSV, string HoTen, string GioiTinh, string NgaySinh, string NganhHoc) {
        cout << "\n==================== THEM SINH VIEN ====================" << endl;
        cout << "\n--- TRANG THAI TRUOC KHI THEM ---" << endl;
        HienThiTatCa();

        vector<int> ds = IndexMaSV.search(MaSV);

        for (int i = 0; i < (int)ds.size(); i++) {
            if (!BangGoc[ds[i]].deleted) {
                cout << "\n>>> Loi: Ma sinh vien da ton tai, khong the them!" << endl;
                return;
            }
        }

        SinhVien sv;
        sv.MaSV= MaSV;
        sv.HoTen = HoTen;
        sv.GioiTinh = GioiTinh;
        sv.NgaySinh= NgaySinh;
        sv.NganhHoc = NganhHoc;
        sv.deleted = false;
        BangGoc.push_back(sv);

        int RowIndex = (int)BangGoc.size() - 1;
        IndexMaSV.insert(MaSV, RowIndex);
        IndexHoTen.insert(HoTen, RowIndex);

        cout << "\n>>> Da them sinh vien thanh cong!" << endl;
        cout << "\n--- TRANG THAI SAU KHI THEM ---" << endl;
        HienThiTatCa();
    }

    void XoaSinhVienTheoMa(string MaSV) {
        cout << "\n==================== XOA SINH VIEN ====================" << endl;
        cout << "\n--- TRANG THAI TRUOC KHI XOA ---" << endl;
        HienThiTatCa();

        vector<int> ds = IndexMaSV.search(MaSV);

        if (ds.empty()) {
            cout << "\n>>> Khong tim thay sinh vien co ma: " << MaSV<< endl;
            return;
        }

        bool DaXoa = false;

        for (int i = 0; i < (int)ds.size(); i++) {
            int idx = ds[i];
            if (!BangGoc[idx].deleted && BangGoc[idx].MaSV== MaSV) {
                BangGoc[idx].deleted = true;
                DaXoa = true;
            }
        }

        if (DaXoa) {
            RebuildIndex();
            cout << "\n>>> Da xoa sinh vien co ma: " << MaSV<< endl;
            cout << "\n--- TRANG THAI SAU KHI XOA ---" << endl;
            HienThiTatCa();
        }
        else {
            cout << "\n>>> Khong co sinh vien hop le de xoa!" << endl;
        }
    }


    void TimTheoMa(string MaSV) {
        cout << "\n==================== TIM THEO MA SV ====================" << endl;
        cout << "\n--- BANG DU LIEU HIEN TAI ---" << endl;
        HienThiBangGoc();

        cout << "\n--- INDEX HIEN TAI ---" << endl;
        HienThiIndex();

        vector<int> ds = IndexMaSV.search(MaSV);

        cout << "\n--- KET QUA TIM KIEM ---" << endl;
        bool TimThay = false;

        for (int i = 0; i < (int)ds.size(); i++) {
            int idx = ds[i];
            if (!BangGoc[idx].deleted && BangGoc[idx].MaSV== MaSV) {
                if (!TimThay) {
                    cout << left
                         << setw(10) << "MaSV"
                         << setw(25) << "Ho ten"
                         << setw(10) << "Gioi Tinh"
                         << setw(15) << "Ngay sinh"
                         << setw(20) << "Nganh hoc"
                         << endl;
                    cout << "----------------------------------------------------------------" << endl;
                }
                cout << left
                     << setw(10) << BangGoc[idx].MaSV
                     << setw(25) << BangGoc[idx].HoTen
                     << setw(10) << BangGoc[idx].GioiTinh
                     << setw(15) << BangGoc[idx].NgaySinh
                     << setw(20) << BangGoc[idx].NganhHoc
                     << endl;

                TimThay = true;
            }
        }

        if (!TimThay) {
            cout << "Khong tim thay sinh vien!" << endl;
        }
        cout << "\n(Luu y: thao tac tim kiem khong lam thay doi bang goc va index.)" << endl;
    }

    void TimTheoHoTen(string HoTen) {
        cout << "\n==================== TIM THEO HO TEN ====================" << endl;
        cout << "\n--- BANG DU LIEU HIEN TAI ---" << endl;
        HienThiBangGoc();

        cout << "\n--- INDEX HIEN TAI ---" << endl;
        HienThiIndex();

        vector<int> ds = IndexHoTen.search(HoTen);

        cout << "\n--- KET QUA TIM KIEM ---" << endl;
        bool TimThay = false;

        for (int i = 0; i < (int)ds.size(); i++) {
            int idx = ds[i];
            if (!BangGoc[idx].deleted && BangGoc[idx].HoTen == HoTen) {
                if (!TimThay) {
                    cout << left
                         << setw(10) << "MaSV"
                         << setw(25) << "Ho ten"
                         << setw(10) << "Gioi Tinh"
                         << setw(15) << "Ngay sinh"
                         << setw(20) << "Nganh hoc"
                         << endl;
                    cout << "----------------------------------------------------------------" << endl;
                }
                cout << left
                     << setw(10) << BangGoc[idx].MaSV
                     << setw(25) << BangGoc[idx].HoTen
                     << setw(10) << BangGoc[idx].GioiTinh
                     << setw(15) << BangGoc[idx].NgaySinh
                     << setw(20) << BangGoc[idx].NganhHoc
                     << endl;

                TimThay = true;
            }
        }

        if (!TimThay) {
            cout << "Khong tim thay sinh vien!" << endl;
        }
        cout << "\n(Luu y: thao tac tim kiem khong lam thay doi bang goc va index.)" << endl;
    }
};

#endif // QLSV_H
