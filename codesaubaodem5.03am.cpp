#include <iostream>
#include <string>
#include <limits>
#include <iomanip>
#include <sstream>
#include <cctype>

using namespace std;

// Cau truc de luu thong tin sinh vien
struct SinhVien {
    string STT; // So thu tu
    string MSSV; // Ma so sinh vien
    bool kiemTraChiChuCai;
	string Hovaten; // Ho va ten
    string Lop; // Lop
    string Quequan; // Que quan 
    string HocLuc; // Hoc Luc
    string Ngaybatdau; // Ngay bat dau o KTX
    string NhapNgayThangNam;
	string Hoancanh; // Hoan Canh
	bool LaMienGiam; // Chi tieu mien giam tien phong
    SinhVien* Next; // Con tro den sinh vien tiep theo
};

// Cau truc du luu thong tin phong
struct Phong {
    string STT; // So thu tu
    string IdPhong; // ID phong
    bool Codayducosovatchat; // Co day du co so vat chat khong
    SinhVien* Danhsachsinhvien; // Danh sach sinh vien trong phong
    double Chiphidien; // Chi phi dien
    double Chiphinuoc; // Chi phi nuoc
    double TongTienDienNuoc; // Tong chi phi dien nuoc
    bool PhongSach; // Tieu chi sach
    bool PhongDep; // Tieu chi dep
    bool PhongAnToan; // Tieu chi gon gang
    string GiaiThuongPhong; // Giai thuong phong
    Phong* Next; // Con tro den phong tiep theo
};

// Ham Nhap Thong Tin Sinh Vien
string NhapNgayThangNam() {
    int day, month, year;
    char sep1, sep2;
    cin >> day >> sep1 >> month >> sep2 >> year;
    
    // Check the separators and date range validity (simple check)
    if (sep1 != '/' || sep2 != '/' || day < 1 || day > 31 || month < 1 || month > 12 || year < 1900) {
        cout << "Ngay thang khong hop le. Vui long nhap lai theo dinh dang (dd/mm/yyyy).\n";
        return NhapNgayThangNam();  // Recursive call for re-entry
    }

    // Format the date as a string in "dd/mm/yyyy"
    stringstream ss;
    ss << setw(2) << setfill('0') << day << "/"
       << setw(2) << setfill('0') << month << "/"
       << year;
    return ss.str();
}
    
// Ham kiem tra xem chuoi co chi chua ky tu chu cai hay khong
    bool kiemTraChiChuCai(const string& str) {
    for (char c : str) {
        if (!isalpha(c) && c != ' ') { // Kiem tra tung ky tu
            return false; // Neu co ky tu khong phai chu cai hoac khong phai khoang trang, tra ve false
        }
    }
    return true; // Tat ca ky tu deu la chu cai hoac khoang trang
}

// Ham them sinh vien vao danh sach
void ThemSinhVienTaiViTri(SinhVien*& Head, const SinhVien& SinhVienmoi, int viTri) {
    SinhVien* Nodemoi = new SinhVien(SinhVienmoi);
    Nodemoi->Next = NULL;

    if (viTri == 0) {
        // Them vao dau danh sach
        Nodemoi->Next = Head;
        Head = Nodemoi;
    } else {
        SinhVien* Current = Head;
        for (int i = 1; i < viTri - 1 && Current != NULL; i++) {
            Current = Current->Next; // Di chuyen den vi tri truoc vi tri chen
        }
        if (Current != NULL) {
            Nodemoi->Next = Current->Next; // Gan con tro tiep theo cua node moi
            Current->Next = Nodemoi; // Chen node moi vao danh sach
        } else {
            cout << "Vi tri khong hop li!" << endl;
            delete Nodemoi; // Xaa node moi neu khong chen duoc
            return;
        }
    }
}

// Ham xaa sinh vien toi vi tri
void XoaSinhVienTaiViTri(SinhVien*& Head, int viTri) {
    if (Head == NULL) {
        cout << "Danh sach rong!" << endl;
        return;
    }

      SinhVien* Current = Head;

    if (viTri == 0) {
        // Xoa node dau
        Head = Current->Next;
        delete Current;
        return;
    }

    for (int i = 1; i < viTri - 1 && Current != NULL; i++) {
        Current = Current->Next; // Di chuyen den vi tri truoc vi tri can xoa
    }

    if (Current == NULL || Current->Next == NULL) {
        cout << "Vi tri khong hop le!" << endl;
        return;
    }

    SinhVien* Temp = Current->Next; // Node can xoa
    Current->Next = Temp->Next; // Bo qua node can xoa
    delete Temp; // Giai phong bo nho
}

// Ham them phong vao danh sach
void ThemPhong(Phong*& Head, const Phong& Phongmoi) {
    Phong* Nodemoi = new Phong(Phongmoi);
    Nodemoi->Next = Head;
    Nodemoi->Danhsachsinhvien = NULL; Head = Nodemoi;
}

// Ham nhap thong tin sinh vien
void nhapSinhVien(SinhVien*& head) {
    SinhVien sinhVienMoi;

    cout << "Nhap thong tin sinh vien:" << endl;

    // Nhap MSSV
    while (true) {
        cout << "| MSSV: ";
        cin >> sinhVienMoi.MSSV;
        cin.ignore(); // Xoa bo dem de tranh loi getline sau do

        // Kiem tra do dai va xem co phai la 10 ki tu hay khong
        if (sinhVienMoi.MSSV.length() == 10) {
            bool isAllDigits = true;
            bool hasLetter = false;

            for (size_t i = 0; i < sinhVienMoi.MSSV.length(); ++i) {
                char c = sinhVienMoi.MSSV[i];
                if (isdigit(c)) {
                    continue; // Neu la so, tiep tuc
                } else if (isalpha(c)) {
                    hasLetter = true; // Neu la chu cai, danh dau
                } else {
                    isAllDigits = false; // Neu khong phai so va khong phai chu cai, khong hop le
                    break;
                }
            }

            // Kiem tra dieu kien hop le
            if (isAllDigits || (hasLetter && sinhVienMoi.MSSV.length() == 10)) {
                break; // Neu la 10 so hoac 9 so va 1 chu, thoat khoi vong lap
            }
        }

        cout << "MSSV khong hop le. Vui long nhap lai (10 ki tu)." << endl;
    }


    // Nhap ho va ten
    while (true) {
        cout << "| Ho va ten: ";
        getline(cin, sinhVienMoi.Hovaten); // Nhap ho va ten

        // Kiem tra xem ho va ten co hop le khong
        if (!sinhVienMoi.Hovaten.empty() && kiemTraChiChuCai(sinhVienMoi.Hovaten)) {
            break; // Neu hop le, thoat khoi vong lap
        } else {
            cout << "Ho va ten khong hop le. Vui long nhap lai." << endl; // Thong bao loi
        }
    }
     
    // Nhap lop
    while (true) {
        cout << "| Lop: ";
        getline(cin, sinhVienMoi.Lop);
        if (!sinhVienMoi.Lop.empty()) {
            break; // Neu lop khong trong, thoat khoi vong lap
        }
        cout << "Lop khong duoc de trong. Vui long nhap lai." << endl;
    }

    // Nhap Que quan
    
    while (true) {
        cout << "| Que quan: ";
        getline(cin, sinhVienMoi.Quequan);
        
        // Kiem tra xem que quan co rong khong
        if (!sinhVienMoi.Quequan.empty()) {
            bool isValid = true;
            for (size_t i = 0; i < sinhVienMoi.Quequan.length(); ++i) {
                char c = sinhVienMoi.Quequan[i];
                if (!isalpha(c) && c != ' ') { // Chi cho phep ky tu chu va khoang trang
                    isValid = false;
                    break;
                }
            }
            if (isValid) {
                break; // Neu que quan hop le, thoat khoi vong lap
            }
        }
        
        cout << "Que quan khong duoc de trong va phai la ki tu chu. Vui long nhap lai." << endl;
    }
    
    // Nhap hoc luc
    while (true) {
        cout << "| Hoc luc (xuat sac/gioi/kha): ";
        getline(cin, sinhVienMoi.HocLuc);
        if (!sinhVienMoi.HocLuc.empty()) {
            break; // Neu hoc luc khong trong, thoat khoi vong lap
 }
        cout << "Hoc luc de trong. Vui long nhap lai: " << endl;
    }

    // Nhap ngay bat dau
     cout << "| Ngay Bat Dau o (dd/mm/yyyy): ";
    sinhVienMoi.Ngaybatdau = NhapNgayThangNam(); 
    getline(cin, sinhVienMoi.NhapNgayThangNam);

    // Nhap hoan canh
    while (true) {
        cout << "| Hoan canh (ho ngheo/mo coi/binh thuong): ";
        getline(cin, sinhVienMoi.Hoancanh);
        if (!sinhVienMoi.Hoancanh.empty()) {
            break; // Neu hoan canh khong rong, thoat khoi vong lap
        }
        cout << "Hoan canh de trong. Vui long nhap lai: " << endl;
    }

   // Kiem tra xem sinh vien co duoc mien giam hay khong
sinhVienMoi.LaMienGiam = (sinhVienMoi.HocLuc == "xuat sac" && (sinhVienMoi.Hoancanh == "ho ngheo" || sinhVienMoi.Hoancanh == "mo coi"));

    sinhVienMoi.Next = NULL; // Khoi tao con tro tiep theo
    ThemSinhVienTaiViTri(head, sinhVienMoi, 0); // Chen vao danh sach tai vi tri dau tien
}

// Hàm nhap thong tin phong
void NhapPhong(Phong*& Head) {
    Phong PhongMoi;

    cout << "Nhap Thong Tin Phong:" << endl;

    cout << "| ID Phong: ";
    cin >> PhongMoi.IdPhong;
    cin.ignore();

    char CoSoVatChat;
    while (true) {
        cout << "| Phong Co Day Du Co So Vat Chat Khong? (y/n): ";
        cin >> CoSoVatChat;
        if (CoSoVatChat == 'y' || CoSoVatChat == 'Y') {
            PhongMoi.Codayducosovatchat = true;
            break;
        } else if (CoSoVatChat == 'n' || CoSoVatChat == 'N') {
            PhongMoi.Codayducosovatchat = false;
            break;
        } else {
            cout << "Nhap sai. Vui long nhap 'y' hoac 'n'.: " << endl;
        }
    }

   // Nhap so luong ky dien
     double SoKiDien;

    do {
        cout << "| Nhap so luong ki dien: ";
        cin >> SoKiDien;

        // Kiem tra neu viec nhap lieu gap loi (tuc la khong phai so)
        if (cin.fail()) {
            cout << "Nhap sai ban phai nhap mot so. Vui long thu lai: ";
            cin.clear(); // Xoa trang thai loi
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Bo qua cac ki tu khong hop le 
        } else if (SoKiDien < 0) {
            cout << "So ki dien dang am. Vui long thu lai: ";
        } else {
            break; // Thoat khoi vang lap neu nhap dung
        }
    }while (true);

    PhongMoi.Chiphidien = SoKiDien * 2000; // Tinh chi phi dien

    // Nhap so luong khoi nuoc
    double soKhoiNuoc;

    do {
        cout << "| Nhap so luong khoi nuoc: ";
        cin >> soKhoiNuoc;

        // Kiem tra neu viec nhap lieu gap lai (tuc là khong phai so)
        if (cin.fail()) {
            cout << "Nhap sai ban phai nhap mot so. Vui long thu lai: ";
            cin.clear(); // Xoa trang thai loi
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Bo qua cac ki tu khong hop le?
        } else if (soKhoiNuoc < 0) {
            cout << "so khoi nuoc dang am. Vui long thu lai: ";
        } else {
            break; // Thoat khoi vong lap nau nhap dung
        }
       }while (true);

    PhongMoi.Chiphinuoc = soKhoiNuoc * 8000; // Tinh chi phi nuoc
    // Tinh tong chi phi dien va nuoc
    PhongMoi.TongTienDienNuoc = PhongMoi.Chiphidien + PhongMoi.Chiphinuoc; // Tinh tong chi phi dien nuoc
      
    // Giai thuong phong
    char PhongSach, PhongDep, PhongAnToan;
    
    while (true) {
        cout << "| Tieu chi phong sach se (y/n): ";
        cin >> PhongSach;
        if (PhongSach == 'y' || PhongSach == 'Y') {
            PhongMoi.PhongSach = true;
            break;
        } else if (PhongSach == 'n' || PhongSach == 'N') {
            PhongMoi.PhongSach = false;
            break;
        } else {
            cout << "Nhap sai. Vui long nhap 'y' hoac 'n'." << endl;
        }
    }

    while (true) {
        cout << "| Tieu chi phong dep (y/n): ";
        cin >> PhongDep; 
        if (PhongDep == 'y' || PhongDep == 'Y') {
            PhongMoi.PhongDep = true;
            break;
        } else if (PhongDep == 'n' || PhongDep == 'N') {
            PhongMoi.PhongDep = false;
            break;
        } else {
            cout << "Nhap sai. Vui long nhap 'y' hoac 'n'." << endl;
        }
    }

    while (true) {
        cout << "| Tieu chi phong an toan (y/n): ";
        cin >> PhongAnToan;
        if (PhongAnToan== 'y' || PhongAnToan== 'Y') {
            PhongMoi.PhongAnToan= true;
            break;
        } else if (PhongAnToan== 'n' || PhongAnToan== 'N') {
            PhongMoi.PhongAnToan= false;
            break;
        } else {
            cout << "Nhap sai. Vui long nhap 'y' hoac 'n'." << endl;
        }break;
    }

    // Kiem tra so tieu chi dat duoc
    int tieuChiDatDuoc = 0;

    if (PhongMoi.PhongSach) {
        tieuChiDatDuoc++;
    }
    if (PhongMoi.PhongDep) {
        tieuChiDatDuoc++;
    }
    if (PhongMoi.PhongAnToan) {
        tieuChiDatDuoc++;
    }

    // Xac dinh giai thuong
    if (tieuChiDatDuoc == 3) {
        PhongMoi.GiaiThuongPhong = "Giai Nhat"; // Gan giai thuong cho phong
    } else if (tieuChiDatDuoc == 2) {
        PhongMoi.GiaiThuongPhong = "Giai Khuyen Khich"; // Gan giai thuong cho phong
    } else {
        PhongMoi.GiaiThuongPhong = "Khong Dat Giai"; // Gan giai thuong cho phong
    }

    PhongMoi.Danhsachsinhvien = NULL; // Khoi tao danh sach sinh vien rong
    PhongMoi.Next = NULL; // Khoi tao con tro tiep theo
    ThemPhong(Head, PhongMoi);
}

// Hàm in danh sách sinh viên
void InDanhSachSinhVien(SinhVien* Head) {
    cout << "=====================================================================================================================================" << endl;
    cout << " | " << setw(3)   << "STT" 
         << " | " << setw(9)  <<  "MSSV" 
         << " | " << setw(25) <<  "Ho Va Ten" 
         << " | " << setw(11) <<  "Lop" 
         << " | " << setw(14) <<  "Que Quan" 
         << " | " << setw(11) <<  "Hoc Luc" 
         << " | " << setw(15) <<  "Ngay Bat Dau"
         << " | " << setw(12) <<  "Hoan Canh"
         << " | " << setw(10) <<  "Mien Giam"
         << " |"     << endl;
    cout << "=====================================================================================================================================" << endl;

    SinhVien* Current = Head;
    int index = 1; // Bien de dem so thu tu
    while (Current != NULL) {
        cout << " | " 
             << setw(3)   << index // In so thu tu
             << " | " 
             << setw(9)  << Current->MSSV 
             << " | " 
             << setw(25) << Current->Hovaten 
             << " | " 
             << setw(11) << Current->Lop 
             << " | " 
             << setw(14) << Current->Quequan 
             << " | " 
             << setw(11) << Current->HocLuc 
             << " | " 
             << setw(15) << Current->Ngaybatdau
             << " | " 
             << setw(12) << Current->Hoancanh 
             << " | " 
             << setw(10)  << (Current->LaMienGiam ? "Co" : "Khong") 
             << " |"     << endl;

        cout << "-------------------------------------------------------------------------------------------------------------------------------------" << endl;
        Current = Current->Next;
        index++; // Tang so thu tu 
    }
}

// Ham in danh sach phong theo dinh dang bang
void InDanhSachPhong(Phong* Head) {
    cout << "=================================================================================================================================" << endl;
    cout << " | " << setw(5)   << "STT" 
         << " | " << setw(10)  << "Id Phong" 
         << " | " << setw(30) <<  "Co day du do so vat chat" 
         << " | " << setw(19) <<  "So luong sinh vien" 
         << " | " << setw(25) <<  "Tong Tien Dien Nuoc" 
         << " | " << setw(20) <<  "Giai thuong phong" 
         << " |"     << endl;
    cout << "=================================================================================================================================" << endl;


    Phong* Current = Head;
    int index = 1; // Bien de dem so thu tu
    while (Current != NULL) {
        int soSinhVien = 0;
        SinhVien* svCurrent = Current->Danhsachsinhvien;
        while (svCurrent != NULL) {
            soSinhVien++;
            svCurrent = svCurrent->Next;
        }

        cout << " | " 
             << setw(5)  << index 
             << " | " 
             << setw(10) << Current->IdPhong
             << " | " 
             << setw(30) << (Current->Codayducosovatchat ? "Co" : "Khong") 
             << " | " 
             << setw(19) << soSinhVien 
             << " | " 
             << setw(25) << Current->TongTienDienNuoc 
             << " | " 
             << setw(20) << Current->GiaiThuongPhong 
             << " |"     << endl;

        cout << "----------------------------------------------------------------------------------------------------------------------------------" << endl;
        Current = Current->Next;
        index++; // Tang so thu tu
    }
}

// Ham tim sinh vien theo ma so sinh vien
SinhVien* TimSinhVienTheoMSSV(SinhVien* Head, const string& MSSV) {
    SinhVien* Current = Head;
    while (Current != NULL) {
        if (Current->MSSV == MSSV) {
            return Current; // Tim thay sinh vien
        }
        Current = Current->Next;
    }
    return NULL; // Khong tim thay
}

// Ham in danh sach sinh vien duoc mien giam
void InDanhSachSinhVienMienGiam(SinhVien* Head) {
    cout << "Danh Sach Sinh Vien Duoc Mien Giam:" << endl;
    SinhVien* Current = Head;
    while (Current != NULL) {
        if (Current->LaMienGiam) {
            cout << Current->Hovaten << " - MSSV: " << Current->MSSV << endl;
        }
        Current = Current->Next;
    }
}

// Ham Main
int main() {
    Phong* DanhSachPhong = NULL;
    int LuaChon;

    do {
        cout << "\n--------------------- Menu -------------------------------" << endl;
        cout << "1. Nhap Phong" << endl;
        cout << "2. Nhap Sinh Vien Vao Phong" << endl;
        cout << "3. Nhap Sinh Vien Tai Vi Tri" << endl;
        cout << "4. Xoa Sinh Vien Tai Vi Tri" << endl;
        cout << "5. In Danh Sach Sinh Vien Trong Phong" << endl;
        cout << "6. In Danh Sach Cac Phong" << endl;
        cout << "7. Tim Sinh Vien Theo Ma So Sinh Vien" << endl;
        cout << "8. In Danh Sach Sinh Vien Duoc Mien Giam Tien Phong" << endl;
        cout << "0. Thoat" << endl;
        cout << "\n-----------------------------------------------------------" << endl;
        cout << "Chon Mot Tuy Chon: ";
        cin >> LuaChon;

        switch (LuaChon) {
            case 1: {
                NhapPhong(DanhSachPhong);
                break;
            }
            case 2: {
                string IdPhong;
                cout << "Nhap ID Phong De Them Sinh Vien: ";
                cin >> IdPhong;
                Phong* PhongHienTai = DanhSachPhong;
                while (PhongHienTai != NULL && PhongHienTai->IdPhong != IdPhong) {
PhongHienTai = PhongHienTai->Next;
                }
                if (PhongHienTai != NULL) {
                    nhapSinhVien(PhongHienTai->Danhsachsinhvien);
                } else {
                    cout << "Phong Khong Ton Tai!" << endl;
                }
                break;
            }
            case 3: {
                string IdPhong;
                cout << "Nhap ID Phong De Nhap Sinh Vien Tai Vi Tri: ";
                cin >> IdPhong;
                Phong* PhongHienTai = DanhSachPhong;
                while (PhongHienTai != NULL && PhongHienTai->IdPhong != IdPhong) {
                    PhongHienTai = PhongHienTai->Next;
                }
                if (PhongHienTai != NULL) {
                    SinhVien SinhVienMoi;
                    cout << "Nhap Thong Tin Sinh Vien:" << endl;
                    cout << "| MSSV: ";
                    cin >> SinhVienMoi.MSSV;
                    cin.ignore();

                    cout << "| Ho Va Ten: ";
                    getline(cin, SinhVienMoi.Hovaten);

                    cout << "| Lop: ";
                    getline(cin, SinhVienMoi.Lop);

                    cout << "| Que Quan: ";
                    getline(cin, SinhVienMoi.Quequan);

                    cout << "| Hoc Luc (xuat sac/gioi/kha): ";
                    getline(cin, SinhVienMoi.HocLuc);

                    cout << "| Ngay Bat Dau: ";
                    getline(cin, SinhVienMoi.NhapNgayThangNam);

                    cout << "| Hoan Canh (ho ngheo/mo coi/binh thuong): ";
                    getline(cin, SinhVienMoi.Hoancanh);

                    SinhVienMoi.LaMienGiam = (SinhVienMoi.Hoancanh == "ho ngheo" || SinhVienMoi.Hoancanh == "mo coi") &&
                                             (SinhVienMoi.HocLuc == "xuat sac");

                    SinhVienMoi.Next = NULL; // Khoi tao con tro tiep theo
                    int viTri;
                    cout << "Nhap Vi Tri De Chen Sinh Vien: ";
                    cin >> viTri;
                    ThemSinhVienTaiViTri(PhongHienTai->Danhsachsinhvien, SinhVienMoi, viTri);
                    
                    
                } else {
                    cout << "Phong Khong Ton Tai!" << endl;
                }
                break;
            }
            case 4: {
                string IdPhong;
                cout << "Nhap ID Phong De Xoa Sinh Vien Tai Vi Tri: ";
                cin >> IdPhong;
                Phong* PhongHienTai = DanhSachPhong;
                while (PhongHienTai != NULL && PhongHienTai->IdPhong != IdPhong) {
                    PhongHienTai = PhongHienTai->Next;
                }
                if (PhongHienTai != NULL) {
                    int viTri;
                    cout << "Nhap Vi Tri De Xoa Sinh Vien: ";
                    cin >> viTri;
                    XoaSinhVienTaiViTri(PhongHienTai->Danhsachsinhvien, viTri);
                } else {
                    cout << "Phong Khong Ton Tai!" << endl;
                }
                break;
}
            case 5: {
                string IdPhong;
                cout << "Nhap ID Phong De In Danh Sach Sinh Vien: ";
                cin >> IdPhong;
                Phong* PhongHienTai = DanhSachPhong;
                while (PhongHienTai != NULL && PhongHienTai->IdPhong != IdPhong) {
                    PhongHienTai = PhongHienTai->Next;
                }
                if (PhongHienTai != NULL) {
                    InDanhSachSinhVien(PhongHienTai->Danhsachsinhvien);
                } else {
                    cout << "Phong Khong Ton Tai!" << endl;
                }
                break;
            }
            case 6: {
                InDanhSachPhong(DanhSachPhong);
                break;
            }
            case 7: {
                string MSSV;
                cout << "Nhap Ma So Sinh Vien Can Tim: ";
                cin >> MSSV;
                SinhVien* SinhVienTimThay = TimSinhVienTheoMSSV(DanhSachPhong->Danhsachsinhvien, MSSV);
                if (SinhVienTimThay) {
                    cout << "Sinh Vien Tim Thay: " << SinhVienTimThay->Hovaten << endl;
                } else {
                    cout << "Khong Tim Thay Sinh Vien Voi Ma So: " << MSSV << endl;
                }
                break;
            }
            case 8: {
                string IdPhong;
                cout << "Nhap ID Phong De In Danh Sach Sinh Vien Duoc Mien Giam Tien Phong: ";
                cin >> IdPhong;
                Phong* PhongHienTai = DanhSachPhong;
                while (PhongHienTai != NULL && PhongHienTai->IdPhong != IdPhong) {
                    PhongHienTai = PhongHienTai->Next;
                }
                if (PhongHienTai != NULL) {
                    InDanhSachSinhVienMienGiam(PhongHienTai->Danhsachsinhvien);
                } else {
                    cout << "Phong Khong Ton Tai!" << endl;
                }
                break;
            }
            case 0:
                cout << "Thoat Chuong Trinh." << endl;
                break;
            default:
                cout << "Lua Chon Khong Hop Le. Vui Long Thu Lai." << endl;
        }
    } while (LuaChon > 0);

    // Giai phong bo nho
    while (DanhSachPhong != NULL) {
        Phong* PhongTam = DanhSachPhong;
        DanhSachPhong = DanhSachPhong->Next;
        while (PhongTam->Danhsachsinhvien != NULL) {
            SinhVien* SinhVienTam = PhongTam->Danhsachsinhvien;
            PhongTam->Danhsachsinhvien = PhongTam->Danhsachsinhvien->Next;
            delete SinhVienTam;
        }
        delete PhongTam;
    }

    return 0;
}
