
// lay max width, height cua man hinh
int w = GetSystemMetrics(SM_CXSCREEN);
int h = GetSystemMetrics(SM_CYSCREEN);


Window Window;
SubWindow subWindow;
int curMenu = 0, curMenuMuonTra;
int curItem = -1, curItemSach = -1, curDauSach = -1, curSach = -1;
int curItemDG = -1, curDG = -1;
int curItemMT = -1, curMT = -1;
DocGia* curDGMT = NULL;
DauSach* curDSMT = NULL;
Sach* curSachMT = NULL;
Node_ID* nodeStart = NULL;	// random ID doc gia
// toa do con tro chuot hien tai
int mx = -1, my = -1;
int totalPageDauSach = 1, curPageDauSach = 1;
int totalPageSach = 1, curPageSach = 1;

int totalPageDG = 1, curPageDG = 1;
int totalPageDGQuaHan = 1, curPageDGQuaHan = 1;

int totalNhapSach = 0, curNhapSach = 0;
int startIndexSach = -1;

bool sortDGByName = false;
bool canMT = false; // Doc Gia co the muon sach hay khong?
bool canEditTrangThai = true;

EditText* Edit = NULL;


// hoanh do x cua Dau Sach

int XDS[7] = { 10, 90, 420, 500, 720, 775, 930 };
// X Danh Muc Sach
int XDMS[4] = { 960, 1100, 1330, w - 17 };
// X Danh sach Doc Gia
int XDG[7] = { 5, 70, 480, 750, 803, 850, 910 };
// X Muon Tra sach 
int XMT[5] = { 20, 120, 420, 540, 700 };
// X Top 10
int XTT[] = { 80, 130, 220, 580, 690, 940, 1050, 1230, 1380 };


char* TrangThaiSach[15] = { "CHO MUON DUOC", "DA CHO MUON", "DA THANH LY" };
char* PhaiDocGia[5] = { "NAM", "NU" };
char* TTTDocGia[10] = { "KHOA", "HOAT DONG" };
char TTMuonTra[][10] = { "DANG MUON", "DA TRA", "LAM MAT" };

char mess[50];

bool mclick = false;

DS_DocGia DSDG;
DS_DauSach DSDS;
NodeDocGia* TreeDocGia = NULL;

char AppTitle[] = "_QUAN LY THU VIEN_";
char DauSachTitle[] = "DANH SACH DAU SACH";
char ThemDauSach[] = "THEM DAU SACH";
char XoaDauSach[]="XOA DAU SACH";
char HieuChinhDauSach[] = "HIEU CHINH DAU SACH";
char ThemSach[] = "THEM SACH: ";
char NhapSach[] = "NHAP SACH";
char Soluongsach[]="So luong sach:";
char HieuChinhSach[] = "HIEU CHINH SACH";
char ThongBao[] = "THONG BAO:";
char DanhMucSach[80] = "DANH MUC SACH";
char DocGiaTitle[] = "DANH SACH DOC GIA";
char ThemDocGia[] = "THEM DOC GIA";
char HieuChinhDocGia[] = "HIEU CHINH DOC GIA";
char XoaDocGia[] = "XOA DOC GIA";
char MuonSach[] = "MUON SACH";
char TraSach[] = "TRA SACH";
char TopTen[] = "TOP 10 CUON SACH MUON NHIEU NHAT";
char DSDM[] = "CAC SACH DANG MUON";
char DSDMQH[] = "CAC SACH QUA HAN";
// Button Main Menu
int btnHei = 60, btnWid = 300, btnSpace = 80, btnY = 90;
Button btnQLDauSach(100, 50, btnY + btnSpace, btnWid, btnHei, "QUAN LY DAU SACH", 0);
Button btnQLDocGia(101, 50, btnY + 2 * btnSpace, btnWid, btnHei, "QUAN LY DOC GIA", 0);
Button btnQLSach(102, 50, btnY + 3 * btnSpace, btnWid, btnHei, "MUON TRA SACH", 0);
Button btnThongTin(103, 50, btnY + 4 * btnSpace, btnWid, btnHei, "THONG TIN", 0);
Button btnThoat(104, 50, btnY + 5 * btnSpace, btnWid, btnHei, "THOAT", 0);
bool isExit;

//DANH SACH DAU SACH
Button btnQuayVe(201, 10, 10, 100, 50, "< MENU", 0);
Button btnClearTimDauSach(202, 810, 70, 100, 50, "CLEAR", 0);
Button btnPrevDauSach(145, -85 + (XDS[0] + XDS[6]) / 2 - 50 / 2, 500, 70, 50, "<<", 0);
Button btnNextDauSach(204, 20 + 50 + (XDS[0] + XDS[6]) / 2 - 50 / 2, 500, 70, 50, ">>", 0);
Button btnFirstDauSach(145,-105+ -85 + (XDS[0] + XDS[6]) / 2 - 50 / 2, 500, 100, 50, "FIRST", 0);
Button btnLastDauSach(204,75+ 20 + 50 + (XDS[0] + XDS[6]) / 2 - 50 / 2, 500, 100, 50, "LAST", 0);
EditText edTimDauSach(1000, 110, 70, 700, 50, "", "", "Nhap ten sach vao day");

// Them Dau Sach
EditText edThemISBN(1002, XDS[6] + 25, 135, 565, 40, "ISBN :", "", "Chi nhan so va chu cai, toi da 10 ki tu");
EditText edThemTenSach(1003, XDS[6] + 25, 185, 565, 40, "Ten sach :", "", "Chi nhan chu cai va so, toi da 30 ki tu");
EditText edThemSoTrang(1004, XDS[6] + 25, 235, 565, 40, "So trang :", "", "Chi nhan so, toi da 5 ki tu");
EditText edThemTacGia(1005, XDS[6] + 25, 285, 565, 40, "Tac gia :", "", "Chi nhan chu cai, toi da 19 ki tu");
EditText edThemNXB(1006, XDS[6] + 25, 335, 565, 40, "NXB :", "", "Chi nhan so");
EditText edThemTheLoai(1007, XDS[6] + 25, 385, 565, 40, "The loai :", "", "Chi nhan chu cai, toi da 15 ki tu");

Button btnThemDauSach(180, (w - 15 + XDS[6]) / 2, 500, 130, 50, "THEM", 0);//130 do dai cua khung ve chieu ngang 

// Hieu Chinh Dau Sach
EditText edHieuChinhISBN(1008, XDS[6] + 25, 135, 565, 40, "ISBN :", "", "Chi nhan so va chu cai, toi da 10 ki tu");
EditText edHieuChinhTenSach(1009, XDS[6] + 25, 185, 565, 40, "Ten sach :", "", "Chi nhan chu cai va so, toi da 30 ki tu");
EditText edHieuChinhSoTrang(1010, XDS[6] + 25, 235, 565, 40, "So trang :", "", "Chi nhan so, toi da 5 ki tu");
EditText edHieuChinhTacGia(1011, XDS[6] + 25, 285, 565, 40, "Tac gia :", "", "Chi nhan chu cai, toi da 19 ki tu");
EditText edHieuChinhNXB(1012, XDS[6] + 25, 335, 565, 40, "NXB :", "", "Chi nhan so");
EditText edHieuChinhTheLoai(1013, XDS[6] + 25, 385, 565, 40, "The loai :", "", "Chi nhan chu cai, toi da 15 ki tu");

Button btnHieuChinhDauSach(1180,  + (w - 15 + XDS[6]) / 2, 500, 200, 50, "HIEU CHINH", 0);

// Danh Muc Sach
Button btnPrevDanhMucSach(207, -110 + (XDMS[0] + XDMS[3]) / 2, 310, 70, 50, "<<", 0);
Button btnNextDanhMucSach(208, 40 + (XDMS[0] + XDMS[3]) / 2, 310, 70, 50, ">>", 0);
Button btnBackToThemDauSach(210, XDS[6] + 19, 17, 70, 50, "<BACK", 0);
// Nhap Sach
EditText edNhapSoLuongSach(1016, XDMS[0] + 50, 550, 500, 40, "", "", "Toi da 99");
Button btnNhapSoLuongSach(217, (XDMS[0] + XDMS[3]) / 2 - 20, 600, 100, 50, "NHAP", 0);
// Them Sach
EditText edThemMaSach(1014, XDS[6] + 20, 470, 565, 40, "Ma sach :", "", "Tu dong");
EditText edThemTrangThaiSach(1015, XDS[6] + 20, 520, 565, 40, "TT [0,1,2]: ", "", "0:Cho muon duoc- 1:Da cho muon- 2:Da thanh ly", TrangThaiSach);
EditText edThemViTriSach(1017, XDS[6] + 20, 570, 565, 40, "Vi tri :", "", "Toi da 18 ki tu");
Button btnThemSach(100, XDMS[0] + 300, 600 +20, 70, 50, "THEM", 0);
// Hieu Chinh Sach
EditText edHieuChinhMaSach(1014, XDS[6]+20, 500, 565, 40, "Ma sach:", "", "Auto");
EditText edHieuChinhTrangThaiSach(1015, XDS[6]+20, 550, 565, 40, "TT[0,1,2]:", "", "0:Cho muon duoc- 1:Da cho muon- 2:Da thanh ly", TrangThaiSach);
EditText edHieuChinhViTriSach(1015, XDS[6]+20 , 600, 565, 40, "Vi tri :", "", "Toi da 18 ki tu");
Button btnHieuChinhSach(217, XDMS[0] + 450, 435 - 5, 100, 50, "EDIT", 0);
Button btnBackToNhapSach(210, XDMS[0], 435 - 5, 100, 50, "< BACK", 0);

// XOA SACH
Button btnXoaDAUSACH(2210, XDMS[0]+20 , 310, 120, 50, "XOA DS", 0);
// Danh sach Doc Gia

// Danh sach Doc Gia
//Button btnTatCaDocGia(211, 1120, 10, 100, 50, "TAT CA", 0);
//Button btnDocGiaQuaHan(212, 1220, 10, 100, 50, "QUA HAN", 0);
//Button btnSapXepTen(213, 900, 10, 100, 50, "TEN", 0);
//Button btnSapXepMaThe(214, 1000, 10, 100, 50, "MA THE", 0);
//Button btnPrevDocGia(215, 10, 770, 150, 50, "Trang truoc", 0);
//Button btnNextDocGia(216, XDG[5]-150, 770, 150, 50, "Trang sau", 0);
Button btnTatCaDocGia(211, 400, 55, 100, 50, "TAT CA", 0);
Button btnDocGiaQuaHan(212, 500, 55, 100, 50, "QUA HAN", 0);
Button btnSapXepTen(213, 180, 55, 100, 50, "TEN", 0);
Button btnSapXepMaThe(214, 280, 55, 100, 50, "MA THE", 0);
Button btnPrevDocGia(215, 300, 480, 70, 50, "<<", 0);
Button btnNextDocGia(216, 450, 480, 70, 50, ">>", 0);
Button btnFirstDocGia(2151, 195, 480, 100, 50, "FIRST", 0);
Button btnLastDocGia(2161, 525, 480, 100, 50, "LAST", 0);

//NIEN CUSTOM TABLE
//Button btnMaThe(2491, XDG[0] , 122, 90, 42, "Ma the", 0);
//Button btnHo(2492,XDG[1] , 122, 260, 42, "Ho", 0);
//Button btnTen(2493, XDG[2] , 122, 110, 42, "Ten", 0);
//Button btnPhai(2494, XDG[3] , 122, 60, 42, "Phai", 0);
//Button btnTrangThaiThe(2495, XDG[4] , 122, 140, 42, "Trang thai the", 0);
//Button btnSoNgayQuaHan(2496, XDG[5] , 122, 150, 42, "So ngay qua han", 0);

//Button btnPrevDocGiaQH(215, 10, 600, 150, 50, "Trang truoc", 0);
//Button btnNextDocGiaQH(216, XDG[6]-150, 600, 150, 50, "Trang sau", 0);
Button btnPrevDocGiaQH(215, 350, 480, 70, 50, "<<", 0);
Button btnNextDocGiaQH(216, 500, 480, 70, 50, ">>", 0);
Button btnFirstDocGiaQH(2152, 245, 480, 100, 50, "FIRST", 0);
Button btnLastDocGiaQH(2162, 575, 480, 100, 50, "LAST", 0);

// Them Doc Gia 
EditText edThemMaTheDocGia(1002, XDG[6] + 20, 115, 585, 40, "Ma the:", "", "auto");
EditText edThemHoDocGia(1003, XDG[6] + 20, 165, 585, 40, "H & TD:", "", "Toi da 30 ki tu");
EditText edThemTenDocGia(1004, XDG[6] + 20, 215, 585, 40, "Ten:", "", "Toi da 20 ki tu");
EditText edThemPhaiDocGia(1005, XDG[6] + 20, 265, 585, 40, "Phai [0,1]:", "", "0: Nam   -   1: Nu", PhaiDocGia);
EditText edThemTrangThaiTheDocGia(1006, XDG[6] + 20, 315, 585, 40, "TT[0,1]:", "1", "0: Khoa  -  1: Hoat dong", TTTDocGia);

Button btnThemDocGia(205, (XDG[6] + w - 15 + 20) / 2 - 45, 400, 150, 50, "THEM", 0);

// Hieu Chinh Doc Gia
EditText edHieuChinhMaTheDocGia(1002, XDG[6] + 20, 115, 585, 40, "Ma the:", "", "khong cho phep");
EditText edHieuChinhHoDocGia(1003, XDG[6] + 20, 165, 585, 40, "H & TD:", "", "Toi da 30 ki tu");
EditText edHieuChinhTenDocGia(1004, XDG[6] + 20, 215, 585, 40, "Ten:", "", "Toi da 20 ki tu");
EditText edHieuChinhPhaiDocGia(1005, XDG[6] + 20, 265, 585, 40, "Phai [0,1]:", "", "0: Nam   -   1: Nu", PhaiDocGia);
EditText edHieuChinhTrangThaiTheDocGia(1006, XDG[6] + 20, 315, 585, 40, "TT[0,1]:", "1", "0: Khoa  -  1: Hoat dong", TTTDocGia);

Button btnHieuChinhDocGia(205, XDG[6] + 70, 390, 150, 50, "HIEU CHINH", 0);
Button btnBackToThemDocGia(210, XDG[6] + 20, 5, 100, 50, "< BACK", 0);

// Xoa doc gia  


Button btnXacNhanXoaDocGia(220, XDG[6] + 70, 390, 200, 50, "XAC NHAN XOA ?", 0);
Button btnHuyXoaDocGia(220, w - 15 - 155, 390, 150, 50, "QUAY VE", 0);

//// Muon Tra Sach
////Button btnBackToMenu(230, 20, 50, 200, 70, "  < MENU", -1);
//Button btnBackToMenu(230, 10, 5, 100, 50, "< MENU", -1);
////Button btnDocGiaQuaHan(212, 500, 55, 100, 70, "QUA HAN", 0);
//Button btnMuonSach(231, 300, 55, 130, 50, "MUON SACH", -1);
//Button btnTraSach(232, 500, 55, 138, 50, " TRA SACH", -1);
//Button btnTopTen(233, 700, 55, 138, 50, "  TOP 10", -1);

// Muon Tra Sach
//Button btnBackToMenu(230, 10, 50, 130, 70, " < MENU", -1);
//Button btnMuonSach(231, 10, 150, 130, 70, "MUON SACH", -1);
//Button btnTraSach(232, 10, 250, 130, 70, "TRA SACH", -1);
//Button btnTopTen(233, 10, 350, 130, 70, " TOP 10", -1);
Button btnBackToMenu(230, 10, 0, 140, 40, " < MENU", -1);
//Button btnMuonSach(231, 160, 0, (w-180)/3, 40, "         MUON SACH", -1);
//Button btnTraSach(232, ((w-180)/3 +170),0 , (w-180)/3, 40, "         	 TRA SACH", -1);
//Button btnTopTen(233, ((w-180)/3) +180 + (w-180)/3,0 ,-10+ (w-180)/3, 40, "          TOP 10", -1);
Button btnMuonSach(231, 160, 0, (w - 180) / 3, 40, "     MUON SACH", -1);
Button btnTraSach(232, ((w - 180) / 3 + 170), 0, (w - 180) / 3, 40, "     	 TRA SACH", -1);
Button btnTopTen(233, ((w - 180) / 3) + 180 + (w - 180) / 3, 0, -10 + (w - 180) / 3, 40, "       TOP 10", -1);
//Button btnCacSachQuaHan(234, ((w-180)/4) +190 + 2*(w-180)/4 -10 ,0 ,-10+ (w-180)/4, 40, " CAC SACH QUA HAN", -1);	

// Muon sach 
//EditText edNhapMaDGMuonSach(1111, 260, 130, 600, 50, "Nhap ma the :", "", "Nhap ma the doc gia vao day");
EditText edNhapMaDGMuonSach(1111, 130, 70, 470, 50, "", "", "Nhap ma the doc gia vao day");
//EditText edNhapMaSachMuonSach(1112, 250+(w-250)/2 + 20, 130, 600, 50, "Nhap ma sach :", "", "Nhap ma sach doc gia muon vao day");
EditText edNhapMaSachMuonSach(1112, 70 + 80 + w / 2, 70, 460, 50, "", "", "Nhap ma sach doc gia muon");
//EditText edNhapNgayMuonSach(1113, 250+(w-250)/2 + 20, 500, 600, 50, "Ngay muon :", "", "01/01/2020");
EditText edNhapNgayMuonSach(1113, 200 + (w - 250) / 2, 530, 400, 50, "Ngay muon :", "", "01/01/2020");
//Button btnTimMaDG(241, 910, 130, 100, 50, "TIM", 0); 
Button btnTimMaDG(241, 600, 70, 100, 50, "TIM", 0);
//Button btnTimMaSach(242, 250+(w-250)/2 + 10+50+600, 130, 100, 50, "TIM", 0);
Button btnTimMaSach(242, 610 + w / 2, 70, 100, 50, "TIM", 0);
//Button btnXacNhanMuonSach(243, 1400, 600, 150, 50, "MUON SACH", 0);
Button btnXacNhanMuonSach(243, 200 + (w - 250) / 2 + 400, 530, 150, 50, "MUON SACH", 0);

// Tra sach
//EditText edNhapNgayTraSach(1114, 250+(w-250)/2 + 30, 500, 600, 50, "Ngay tra :", "", "01/01/2020");
//Button btnXacNhanTraSach(244, ((w+250)/2 + w)/2 - 75, 600, 150, 50, "TRA SACH", 0);
EditText edNhapNgayTraSach(1114, 70+w/2, 380, 300, 50, "Ngay tra :", "", "01/01/2020");
Button btnXacNhanTraSach(244, 70+w/2, 450, 130, 50, "TRA SACH", 0);

//Button btnLamMatSach(300, ((w+250)/2 + w)/2 - 100, 800, 200, 50, "LAM MAT SACH?", 0);
Button btnLamMatSach(300, 70+w/2 + 140, 450, 180, 50, "LAM MAT SACH?", 0);


//Button btnXacNhanLamMatSach(301, w/2+300, 800, 200, 50, "XAC NHAN", 0);
//Button btnHuyLamMatSach(302, w-15-300, 800, 200, 50, "HUY", 0); 
//Button btnXacNhanLamMatSach(301, ((w + 250) / 2 + w) / 2 - 180, 390, 150, 50, "XAC NHAN", 0);
//Button btnHuyLamMatSach(302, 150 + ((w + 250) / 2 + w) / 2 - 100, 390, 100, 50, "HUY", 0);
Button btnXacNhanLamMatSach(301,400+ w/2, 440, 130, 50, "XAC NHAN", 0);
Button btnHuyLamMatSach(302, 400+ w/2 +140, 440, 80, 50, "HUY", 0);


void ClearScreen();
void DrawMenu();
void ButtonEffect(Button& btn);
void MenuEvent();
void Event();
void SetMenuSelect(int menuID);
void DrawDanhSachDauSach();
void RunDauSach();
void DauSachEvent();
void DrawBorderList();
void DrawBorderListSach();
void DrawBorderListSachQuaHan();
void DrawList();
void DrawThemDauSach();
void DrawHieuChinhDauSach();
void DrawHieuChinhDauSachDone();
void DrawDanhMucSach();
void DrawNhapSach();
void DrawQuayvekhixoadausach();
void ClearLayoutListDauSach();
void ClearLayoutSach();
void Clearthongbaoxoadausachcosach();
void ClearLayoutDanhMucSach();
void ClearContentHieuChinhSach();
void ItemEvent();
void AutoCreateMaSach();
int GetItemPosition(int y);
int GetItemSachPosition(int y);
void ClickEvent();
void ItemLeftMouseClick();
void ItemRightMouseClick();
void KbEvent();
void DrawItemDauSach(int, int);
void DrawItemSach(Sach& sach, int i);
void ClearContentThemDauSach();

void RunDocGia();
void DocGiaEvent();
void DrawDanhSachDocGia();
void DrawBorderDSDocGia();
void DrawListDocGia(bool reload = false);
void ClearRightLayoutDocGia();

void Scan(EditText*& txt, int maxn, ScanType type, int strartLimit = 0, int endLimit = 0);
void ScanTimDauSach(EditText*& txt, int& n, int maxn, char c);
void ScanTextNumber(EditText*& txt, int& n, char c);
void ScanTextSpace(EditText*& txt, int& n, char c);
void ScanTextOnly(EditText*& txt, int& n, char c);
void ScanNumber(EditText*& txt, int& n, char c);
void ScanNumberGreater0(EditText*& txt, int& n, char c);
void ScanDate(EditText*& txt, int& n, char c);
void ScanLimit(EditText*& txt, int& n, char c, int start, int end);
void ScanMaSach(EditText*& txt, int& n, char c);
void ClearStream();

void DrawThemDocGia(bool genNewID = true);
void DrawItemDocGia(DocGia& docgia, int i);
void DrawItemDocGiaQuaHan(DocGia& docgia, int soNgayQH, int i);
bool ChecHieuCHinhDocGia();
void DrawHieuChinhDocGiaDone();
bool CheckThemDocGia();
void ClearContentHieuChinhDocGia();
void ClearContentThemDocGia();
void DuyetDGTheoMaThe(NodeDocGia*& node, int& i);
void ItemDocGiaEvent();
int GetItemDocGiaPosition(int y);
void ClearLayoutListDocGia();
void DrawHieuChinhDocGia();
void ItemDGLeftMouseClick();
bool CheckHieuChinhDocGia();
void ButtonSwitchClick();
void ItemDGRightMouseClick();
void DrawXoaDocGia(int i);
void ClearLayoutListDocGiaQuaHan();
void DrawBorderDSDocGiaQuaHan();
void DeleteMemoryDocGia(NodeDocGia*& node);

void RunMuonTra();
void MuonTraEvent();
void SetMenuMuonTraSelect(int menuID);
void ClearLayoutMainMuonTra();
void DrawBorderMuonTra();
void DrawMuonSach();
void DrawTraSach();
void DrawTopTen();
void DrawCacSachQuaHan();
void DrawThongTinDocGia();
void ClearLayoutLeftMuonTra();
void ClearLayoutRightMuonTra();
void DrawThongTinSach();
bool CheckDate(char* s);
void ItemMTEvent();
void DrawItemMT(int i);
void ItemMTClick();
void DrawThongTinSachTra(int itemMT);
int TotalDocGia(NodeDocGia*& TreeDG);
void DrawLamMatSach();

void DemSoLanMuonSach(DocGia docgia, TopSach& topsach);
void DuyetDocGia(NodeDocGia*& nodeDG, TopSach& topsach);

void RunThongTin();
void ThongTinEvent();

void MoveToNextEditText();
void MoveToPrevEditText();


void KbEvent() {
	if (GetAsyncKeyState(VK_LEFT) || GetAsyncKeyState(VK_RIGHT)) {
		ClearStream();
		return;
	}

	if (GetAsyncKeyState(VK_DOWN)) {// di duyen xuong
		ClearStream();
		if (Edit != NULL) {
			int n = strlen(Edit->content);
			Edit->draw();
			Edit->content[n] = '\0';
			MoveToNextEditText();// doi toi cho can chinh sua tiep theo
		}
		return;
	}
	else if (GetAsyncKeyState(VK_UP)) {// di chuyen len
		ClearStream();
		if (Edit != NULL) {
			int n = strlen(Edit->content);
			Edit->draw();
			Edit->content[n] = '\0';
			MoveToPrevEditText();// quay nguoc lai cho hoi nay
		}
		return;
	}

	if (Edit != NULL) {
		int n = strlen(Edit->content);
		Edit->content[n] = '_';// dau cuoi cua dong chu minh viet ra
		Edit->draw();
		Edit->content[n] = '\0';// ky tu rong o cuoi chuoi

		if (curMenu == btnQLDauSach.id) {
			if (Edit == &edTimDauSach) {
				Scan(Edit, 30, FIND_DS);
			}
			if (Window == THEM_DAU_SACH) {
				if (Edit == &edThemISBN) {
					Scan(Edit, 10, ISBN);
				}
				else if (Edit == &edThemTenSach) {
					Scan(Edit, 30, TEXT_NUMBER);
				}
				else if (Edit == &edThemSoTrang) {
					Scan(Edit, 5, ONLY_NUMBER_GREATER_0);// chi co so
				}
				else if (Edit == &edThemTacGia) {
					Scan(Edit, 19, SPACE_TEXT);// nhap chu co dau cach
				}
				else if (Edit == &edThemNXB) {
					Scan(Edit, 4, ONLY_NUMBER_GREATER_0);// chi co so
				}
				else if (Edit == &edThemTheLoai) {
					Scan(Edit, 15, SPACE_TEXT);
				}

			}
			else if (Window == HIEU_CHINH_DAU_SACH) {
				if (Edit == &edHieuChinhISBN) {
					Scan(Edit, 5, ISBN);
				}
				else if (Edit == &edHieuChinhTenSach) {
					Scan(Edit, 30, TEXT_NUMBER);
				}
				else if (Edit == &edHieuChinhSoTrang) {
					Scan(Edit, 5, ONLY_NUMBER_GREATER_0);
				}
				else if (Edit == &edHieuChinhTacGia) {
					Scan(Edit, 19, SPACE_TEXT);
				}
				else if (Edit == &edHieuChinhNXB) {
					Scan(Edit, 4, ONLY_NUMBER_GREATER_0);
				}
				else if (Edit == &edHieuChinhTheLoai) {
					Scan(Edit, 15, SPACE_TEXT);
				}

			}
			else if (Window == DANH_MUC_SACH) {
				if (subWindow == NHAP_SACH) {
					if (Edit == &edNhapSoLuongSach) {
						Scan(Edit, 2, ONLY_NUMBER_GREATER_0);			
						
					}
				}
				else if (subWindow == THEM_SACH) {
					if (Edit == &edThemTrangThaiSach) {
						Scan(Edit, 1, LIMIT_CHARACTER, '0', '2');
					}
					else if (Edit == &edThemViTriSach) {
						Scan(Edit, 18, TEXT_NUMBER);
					}
				}
				else if (subWindow == HIEU_CHINH_SACH) {
					if (Edit == &edHieuChinhTrangThaiSach) {
						Scan(Edit, 1, LIMIT_CHARACTER, '0', '2');
					}
					else if (Edit == &edHieuChinhViTriSach) {
						Scan(Edit, 20, TEXT_NUMBER);
					}
				}

			}
		}
		else if (curMenu == btnQLDocGia.id) {
			if (Window == THEM_DOC_GIA) {
				if (Edit == &edThemHoDocGia) {
					Scan(Edit, 30, SPACE_TEXT);
				}
				else if (Edit == &edThemTenDocGia) {
					Scan(Edit, 20, ONLY_TEXT);
				}
				else if (Edit == &edThemPhaiDocGia) {
					Scan(Edit, 1, LIMIT_CHARACTER, '0', '1');
				}
				else if (Edit == &edThemTrangThaiTheDocGia) {
					Scan(Edit, 1, LIMIT_CHARACTER, '0', '1');
				}

			}
			else if (Window == HIEU_CHINH_DOC_GIA) {
				if (Edit == &edHieuChinhHoDocGia) {
					Scan(Edit, 30, SPACE_TEXT);
				}
				else if (Edit == &edHieuChinhTenDocGia) {
					Scan(Edit, 20, ONLY_TEXT);
				}
				else if (Edit == &edHieuChinhPhaiDocGia) {
					Scan(Edit, 1, LIMIT_CHARACTER, '0', '1');
				}
				else if (Edit == &edHieuChinhTrangThaiTheDocGia) {
					Scan(Edit, 1, LIMIT_CHARACTER, '0', '1');
				}
			}
			else if (Window == XOA_DOC_GIA) {

			}
		}
		else if (curMenu == btnQLSach.id) {
			if (Edit == &edNhapMaDGMuonSach) {
				Scan(Edit, 5, ONLY_NUMBER);
			}
			else if (Edit == &edNhapMaSachMuonSach) {
				Scan(Edit, 10, MASACH);
			}
			else if (Edit == &edNhapNgayMuonSach) {
				Scan(Edit, 10, DATE_TIME);
			}

			if (Edit == &edNhapNgayTraSach) {
				Scan(Edit, 10, DATE_TIME);
			}
		}
	}
	else {
		ClearStream();
	}
}

void SetMenuSelect(int menuID) {// menu lua chon
	if (curMenu != menuID) {
		curMenu = menuID;
		ClearScreen();

		if (curMenu == 0) {
			DrawMenu();
		}
		else if (menuID == btnQLDauSach.id) {
			RunDauSach();
		}
		else if (menuID == btnQLDocGia.id) {
			RunDocGia();
		}
		else if (menuID == btnQLSach.id) {
			RunMuonTra();
		}
		else if (menuID == btnThongTin.id) {
			RunThongTin();
		}
	}
}
// hieu ung mau
void ButtonEffect(Button& btn) {

	if (btn.isChoose) return;

	if (btn.isMouseHover(mousex(), mousey())) {
		if (btn.isHover == false) {
			btn.isHover = true;
			btn.draw();
		}
	}
	else {
		if (btn.isHover == true) {
			btn.isHover = false;
			btn.draw();
		}
	}
}
// tiep theo
void MoveToNextEditText() {
	if (Edit == &edThemISBN) Edit = &edThemTenSach;
	else if (Edit == &edThemTenSach) Edit = &edThemSoTrang;
	else if (Edit == &edThemSoTrang) Edit = &edThemTacGia;
	else if (Edit == &edThemTacGia) Edit = &edThemNXB;
	else if (Edit == &edThemNXB) Edit = &edThemTheLoai;
	//	else if(Edit == &edThemTheLoai) Edit = NULL;

	if (Edit == &edHieuChinhTenSach) Edit = &edHieuChinhSoTrang;
	else if (Edit == &edHieuChinhSoTrang) Edit = &edHieuChinhTacGia;
	else if (Edit == &edHieuChinhTacGia) Edit = &edHieuChinhNXB;
	else if (Edit == &edHieuChinhNXB) Edit = &edHieuChinhTheLoai;
	//	else if(Edit == &edHieuChinhTheLoai) Edit = NULL;

	if (Edit == &edThemMaTheDocGia) Edit = &edThemHoDocGia;
	else if (Edit == &edThemHoDocGia) Edit = &edThemTenDocGia;
	else if (Edit == &edThemTenDocGia) Edit = &edThemPhaiDocGia;
	else if (Edit == &edThemPhaiDocGia) Edit = &edThemTrangThaiTheDocGia;
	//	else if(Edit == &edThemTrangThaiTheDocGia) Edit = NULL;

	if (Edit == &edHieuChinhHoDocGia) Edit = &edHieuChinhTenDocGia;
	else if (Edit == &edHieuChinhTenDocGia) Edit = &edHieuChinhPhaiDocGia;
	else if (Edit == &edHieuChinhPhaiDocGia) Edit = &edHieuChinhTrangThaiTheDocGia;
	//	else if(Edit == &edHieuChinhTrangThaiTheDocGia) Edit = NULL;
}
// quay lai
void MoveToPrevEditText() {
	//	if(Edit == &edThemISBN) Edit = &edThemTenSach;
	if (Edit == &edThemTenSach) Edit = &edThemISBN;
	else if (Edit == &edThemSoTrang) Edit = &edThemTenSach;
	else if (Edit == &edThemTacGia) Edit = &edThemSoTrang;
	else if (Edit == &edThemNXB) Edit = &edThemTacGia;
	else if (Edit == &edThemTheLoai) Edit = &edThemNXB;

	//	if(Edit == &edHieuChinhTenSach) Edit = &edHieuChinhSoTrang;
	if (Edit == &edHieuChinhSoTrang) Edit = &edHieuChinhTenSach;
	else if (Edit == &edHieuChinhTacGia) Edit = &edHieuChinhSoTrang;
	else if (Edit == &edHieuChinhNXB) Edit = &edHieuChinhTacGia;
	else if (Edit == &edHieuChinhTheLoai) Edit = &edHieuChinhNXB;

	//	if(Edit == &edThemMaTheDocGia) Edit = &edThemHoDocGia;
	//	if(Edit == &edThemHoDocGia) Edit = &edThemMaTheDocGia;
	if (Edit == &edThemTenDocGia) Edit = &edThemHoDocGia;
	else if (Edit == &edThemPhaiDocGia) Edit = &edThemTenDocGia;
	else if (Edit == &edThemTrangThaiTheDocGia) Edit = &edThemPhaiDocGia;

	//	if(Edit == &edHieuChinhHoDocGia) Edit = &edHieuChinhTenDocGia;
	if (Edit == &edHieuChinhTenDocGia) Edit = &edHieuChinhHoDocGia;
	else if (Edit == &edHieuChinhPhaiDocGia) Edit = &edHieuChinhTenDocGia;
	else if (Edit == &edHieuChinhTrangThaiTheDocGia) Edit = &edHieuChinhPhaiDocGia;
}

// ham san quan trong     
void Scan(EditText*& txt, int maxn, ScanType type, int startLimit, int endLimit) {
	if (txt == NULL) return;
	int mx = -1, my = -1, mrx = -1, mry = -1;
	int n = strlen(txt->content);//

	getmouseclick(WM_LBUTTONDOWN, mx, my);
	clearmouseclick(WM_LBUTTONDOWN);

	getmouseclick(WM_RBUTTONDOWN, mrx, mry);
	clearmouseclick(WM_RBUTTONDOWN);

	if (((mx != -1 && my != -1) || (mrx != -1 && mry != -1)) && (!txt->isMouseHover(mx, my))) {
		txt->content[n] = '\0';
		txt->draw();
		txt = NULL;
		return;
	}

	if (kbhit()) {
		char c = getch();
		// bat nhap 1 ki tu c
		if (c == BACKSPACE && type != FIND_DS) {//dau xoa va lui lai
			if (n > 0) {
				txt->content[n--] = ' ';
				txt->content[n] = ' ';
			}
		}
		else if (c == ENTER) {//nhap
			txt->draw();
			txt->content[n] = '\0';
			//			txt = NULL;

						// animation
			MoveToNextEditText();// lenh tiep theo 

			return;
		}
		else if (n < maxn) {

			if (type == ONLY_NUMBER) {
				ScanNumber(txt, n, c);
				
			}
			else if (type == ONLY_NUMBER_GREATER_0) {
				ScanNumberGreater0(txt, n, c);
			}
			else if (type == ONLY_TEXT) {
				ScanTextOnly(txt, n, c);
			}
			else if (type == SPACE_TEXT) {
				ScanTextSpace(txt, n, c);
			}
			else if (type == TEXT_NUMBER) {
				ScanTextNumber(txt, n, c);
			}
			else if (type == DATE_TIME) {
				ScanDate(txt, n, c);
			}
			else if (type ==  LIMIT_CHARACTER) {
				ScanLimit(txt, n, c, startLimit, endLimit);
			}
			else if (type == ISBN) {
				ScanNumber(txt, n, c);
				ScanTextOnly(txt, n, c);
			}
			else if (type == MASACH) {
				ScanMaSach(txt, n, c);
			}
		}
		if (type == FIND_DS) ScanTimDauSach(txt, n, maxn, c);

		txt->content[n] = '_';
		txt->draw();
		txt->content[n] = '\0';
	}
}
// dung cho cac truong hop nhap trang thai sach 0 hoac 1, 2
void ScanLimit(EditText*& txt, int& n, char c, int start, int end) {
	if (c >= start && c <= end) {
		txt->content[n++] = c;
	}
}
// ngay
void ScanDate(EditText*& txt, int& n, char c) {
	int cnt = 0;
	//18/03/2000
	for (int i = 0; i < n; i++) {
	//	cout<<"\nLap lan thu: "<<i;
		if (txt->content[i] == '/') cnt++;
	//	cout<<"\ncnt= "<<cnt;
	}

	if (c >= '0' && c <= '9') {
		txt->content[n++] = c;
	}
	//18/03/2000
	else if (c == '/' && cnt < 2 && n> 0 && txt->content[n - 1] != '/') {// ngan khum cho hai dau '/' gan nhau
	
		txt->content[n++] = c;
	}
}

// toi uu nhap so ma  doc gia muon sach
void ScanNumber(EditText*& txt, int& n, char c) {
	if (c >= '0' && c <= '9') {
		txt->content[n++] = c;
		
		
	}
}
// toi uu ma sach
void ScanMaSach(EditText*& txt, int& n, char c) {
	if (c >= '0' && c <= '9') {
		txt->content[n++] = c;
	}
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) {//
		txt->content[n++] = toupper(c);// chu in hoa
	}
	if (c == '-') {
		txt->content[n++] = c;
	}
}
// toi uu nhap so trang, NXB
void ScanNumberGreater0(EditText*& txt, int& n, char c) {
	
	if (c >= '0' && c <= '9') {
		if (n == 0 && c == '0') return;// so trang voi nam k the co 0 dc
		txt->content[n++] = c;
	}
}

    
// nhap rieng chu khi nhap the loai va ten tac gia
void ScanTextOnly(EditText*& txt, int& n, char c) {
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) {//
		txt->content[n++] = toupper(c);
	}
}
// dung cho cac ham nhap chu co khoang cach
void ScanTextSpace(EditText*& txt, int& n, char c) {
	if (c == SPACE) {
		if (n > 0 && txt->content[n - 1] != ' ')//n='/0'
			txt->content[n++] = ' ';
	}
	else if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) {
		txt->content[n++] = toupper(c);
	}
}
// nhap cho cac truong hop ca so lan chu vi tri sach, ten sach
void ScanTextNumber(EditText*& txt, int& n, char c) {
	// Chu cai, so, dau cach, dau phay
	if (c == SPACE) {//dau cach
		if (n > 0 && txt->content[n - 1] != ' ')
			txt->content[n++] = ' ';
	}
	else if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) {
		txt->content[n++] = toupper(c);
	}
	else if (c >= '0' && c <= '9') {
		txt->content[n++] = c;
	}
	else if (c == ',') {
		txt->content[n++] = c;
	}
}
// toi uu tim dau sach, n la so ki tu
void ScanTimDauSach(EditText*& txt, int& n, int maxn, char c) {
	if (c == BACKSPACE) {// phim  xoa 
		if (n > 0) {
			txt->content[n--] = ' ';
			txt->content[n] = ' ';
		}
	}
	if (n < maxn) {
		if (c == SPACE) {
			if (n > 0 && txt->content[n - 1] != ' ')
				txt->content[n++] = ' ';
		}
		else if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) {//
			txt->content[n++] = toupper(c);
		}else if (c >= '0' && c <= '9') {
		    txt->content[n++] = c;
	    }
	}
 
	txt->content[n] = '\0';
	//					strfile       m
	GetListNodes(DSDS, txt->content, sizeListIndexDauSachSearch);
	curPageDauSach = 1;
	DrawList();

}

void ClearStream() {
	while (kbhit()) {
		char c = getch();
	}
}

void DrawXoaDauSachDone();


