//==================DO HOA============================
void RunDauSach() {
	strcpy(mess, "");
	ClearContentThemDauSach();

	setlinestyle(SOLID_LINE, 0, 1);
	line(XDS[6] + 10, 0, XDS[6] + 10, h);
	//setcolor(1);
	setfillstyle(1,1);
	bar(XDS[6]+5,0,XDS[6]+15,h);
//	bar(XDS[6]+10,0, XDS[6]+20, h);
	
	
	setlinestyle(SOLID_LINE, 0, 10);
    setcolor(1);
    rectangle(5,5, 1530, 800);
	
	DrawDanhSachDauSach();
	

	DrawList();
	Window = THEM_DAU_SACH;
	subWindow = NHAP_SACH;

	

	if (Window == THEM_DAU_SACH) {
		DrawThemDauSach();
		
	}
	else if (Window == HIEU_CHINH_DAU_SACH) {
		DrawHieuChinhDauSach();
	}
	else if (Window == DANH_MUC_SACH) {
		DrawDanhMucSach();
		if (subWindow == NHAP_SACH) {
			DrawNhapSach();
		}
	}
}

// mo nay la khung DANH SACH DAU SACH
void DrawDanhSachDauSach() {
	settextstyle(BOLD_FONT, HORIZ_DIR, 4);
	setcolor(TEXT_TITLE_COLOR);
	outtextxy((XDS[0] + XDS[6]) / 2 - textwidth(DauSachTitle) / 2, 15, DauSachTitle);//CHU

	btnQuayVe.draw();//ve "MENU"
	btnClearTimDauSach.draw();//ve o "clear" tim
	btnPrevDauSach.draw();// ve"Trang truoc"
	btnNextDauSach.draw();//ve "Trang sau";

	edTimDauSach.draw();//tim dau sach- nhap ten dau sach vao day
	
	
	btnFirstDauSach.draw();
	btnLastDauSach.draw();
	
	setcolor(BORDER_COLOR);
	outtextxy(20, 80,"Nhap ten sach : ");//CHU


}

void ClearRightLayout() {
	setfillstyle(SOLID_FILL, BG_COLOR);
	bar(XDS[6] + 15, 10, 1527, 795);
	
}
//VE DANH MUC SACH
void DrawDanhMucSach() {
	settextstyle(BOLD_FONT, HORIZ_DIR, 2);
	setcolor(TEXT_TITLE_COLOR);//mau vang
	setbkcolor(BG_COLOR);//mau den
	char t[50];
	sprintf(t, "%s: %s", DanhMucSach, DSDS.nodes[curDauSach]->tensach);
	outtextxy((XDMS[0] + XDMS[3]) / 2 - textwidth(t) / 2.2, 23, t);

	DrawBorderListSach();//ve cai khung to cua danh muc sach

	setcolor(BORDER_COLOR);//mau chu tim
	settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 2);
	char ch[3][20] = { "Ma sach", "Trang thai", "Vi tri" };

	for (int i = 0; i < 3; i++) {
		setbkcolor(BG_COLOR);
		outtextxy(XDMS[i] + (XDMS[i + 1] - XDMS[i]) / 2 - textwidth(ch[i]) / 2, 102 - textheight("V") / 2, ch[i]);
	}
	//  phan trang
	totalPageSach = (DSDS.nodes[curDauSach]->soluong - 1) / 4 + 1;
	setcolor(TEXT_TITLE);
	//lay sach theo vi tri
	NodeSach* node = GetNodeSach(DSDS.nodes[curDauSach]->First, 4 * (curPageSach - 1));//vi tri
	//page 1 thi return ve no vi tri 0 node->next;
	// neu curpage sach =1 thi tra ve node co vi tri dau tien ne, tu do chay den 4 sach tiep theo
	for (int i = 0; node != NULL && i < 4; node = node->next) {
	//	cout<<"gia tri cua curpagesach la: "<<curPageSach;
		DrawItemSach(node->sach, i++);
	}


	// num page
	settextstyle(BOLD_FONT, HORIZ_DIR, 2);
	char chPage[20];
	sprintf(chPage, "%d / %d", curPageSach, totalPageSach);//trang sach hien tai/so luong trang sach
	outtextxy(XDMS[0] + (XDMS[3] - XDMS[0]) / 2 - textwidth(chPage) / 2, 325, chPage);


	btnBackToThemDauSach.draw();//BACK
	btnPrevDanhMucSach.draw();//TRANG TRUOC
	btnNextDanhMucSach.draw();//TRANG SAU
	//btnXoasachnhapdu.draw();//XOA SACH
	btnXoaDAUSACH.draw();

	// tips//CLICK chuot trai, hieu chinh sach
	settextstyle(BOLD_FONT, HORIZ_DIR, 2);
//	setcolor(TIPS);//
//	setlinestyle(SOLID_LINE, 0, 3);
//	rectangle(XDMS[0], 740, XDMS[3], 782);
//	outtextxy(XDMS[0] + 20, 755, "Click chuot trai: Hieu chinh sach");
	setcolor(TIPS);
	rectangle(XDMS[0], 730, XDMS[3], 790);
	outtextxy(XDMS[0] + 20, 735, " _________Huong dan su dung__________");
	outtextxy(XDMS[0] + 20, 765, " * Click chuot trai: Hieu chinh sach ");
}
//NHAP SACH CHO TUNG DAU SACH, THEM NHA
//THEM SACH
void DrawNhapSach() {
	ClearLayoutSach();
	settextstyle(BOLD_FONT, HORIZ_DIR, 3);
	setbkcolor(BG_COLOR);
	setcolor(TEXT_TITLE_COLOR);
	outtextxy((XDMS[0] + XDMS[3]) / 2 - textwidth(NhapSach) / 2, 480, NhapSach);
	edNhapSoLuongSach.draw();//toi da 99
	btnNhapSoLuongSach.draw();//THEM
	
	setcolor(BORDER_COLOR);
	outtextxy(XDS[6]+20,560 , Soluongsach);
}
// table THEM SACH vo dau sach o phan danh muc sach  sau khi bam so luong thi bang nay hien ra
void DrawThemSach() {
	ClearLayoutSach();
	AutoCreateMaSach();
	strcpy(edThemTrangThaiSach.content, "0");

	btnThemSach.draw();
	edThemMaSach.draw();
	edThemTrangThaiSach.draw();
	edThemViTriSach.draw();


	char ch[30], c[3];

	sprintf(ch, "%s %d / %d", ThemSach, curNhapSach, totalNhapSach);
	settextstyle(BOLD_FONT, HORIZ_DIR, 3);
	setcolor(TEXT_TITLE_COLOR);
	outtextxy((XDMS[0] + XDMS[3]) / 2 - textwidth(ch) / 2, 430, ch);
	
	setlinestyle(SOLID_LINE, 0, 3);
	setcolor(TIPS);
	//rectangle(XDMS[0], 685, XDMS[3], 735);

	setfillstyle(SOLID_FILL, BG_COLOR);
	bar(XDMS[0] + 5, 690, XDMS[3] - 5, 730);
	settextstyle(BOLD_FONT, HORIZ_DIR, 2);
	//outtextxy(XDMS[0] + 20, 715 - textheight(ThongBao) / 2, ThongBao);

	// Draw mess
	//outtextxy(XDMS[0] + 50 + textwidth(ThongBao), 715 - textheight(ThongBao) / 2, mess);
	outtextxy(XDMS[0] , 700 , mess);
}
// HIEU CHINH SACH O DANH MUC SACH
void DrawHieuChinhSach() {
	ClearLayoutSach();

	settextstyle(BOLD_FONT, HORIZ_DIR, 3);
	setcolor(TEXT_TITLE_COLOR);
	setbkcolor(BG_COLOR);
	outtextxy((XDMS[0] + XDMS[3]) / 2 - textwidth(HieuChinhSach) / 2, 435 - 5, HieuChinhSach);

	btnHieuChinhSach.draw();//EDIT
	edHieuChinhMaSach.draw();
	edHieuChinhTrangThaiSach.draw();
	edHieuChinhViTriSach.draw();
	btnBackToNhapSach.draw();//BACK

	setlinestyle(SOLID_LINE, 0, 3);
	setcolor(TIPS);
//	rectangle(XDMS[0], 685, XDMS[3], 735);

	setfillstyle(SOLID_FILL, BG_COLOR);
	bar(XDMS[0] + 5, 690, XDMS[3] - 5, 730);
	settextstyle(BOLD_FONT, HORIZ_DIR, 2);
	//outtextxy(XDMS[0] + 20, 715 - textheight(ThongBao) / 2, ThongBao);

	// Draw mess
	//outtextxy(XDMS[0] + 50 + textwidth(ThongBao), 700 - textheight(ThongBao) / 2, mess);
	outtextxy(XDMS[0] , 670 , mess);
}
// THEM DAU SACH
void DrawThemDauSach() {


	setbkcolor(BG_HOME_COLOR);
	settextstyle(BOLD_FONT, HORIZ_DIR, 4);
	setcolor(TEXT_TITLE_COLOR);
	outtextxy((w - 15 + XDS[6] + 20) / 2 - textwidth(ThemDauSach) / 2, 15, ThemDauSach);

	settextstyle(BOLD_FONT, HORIZ_DIR, 2);
	setcolor(TEXT_TITLE_COLOR);
	setbkcolor(BG_HOME_COLOR);
	outtextxy(XDS[6] + 60, 470 - textheight(ThongBao) / 2, ThongBao);

	setfillstyle(SOLID_FILL, BG_HOME_COLOR);
	outtextxy(XDS[6] + 60 + 20 + textwidth(ThongBao), 470 - textheight(ThongBao) / 2, mess);

	edThemISBN.draw();
	edThemTenSach.draw();
	edThemSoTrang.draw();
	edThemTacGia.draw();
	edThemNXB.draw();
	edThemTheLoai.draw();

	btnThemDauSach.draw();
}

//HIEU CHINH DAU SACH
void DrawHieuChinhDauSach() {


	setbkcolor(BG_HOME_COLOR);
	settextstyle(BOLD_FONT, HORIZ_DIR, 4);
	setcolor(TEXT_TITLE_COLOR);
	outtextxy((w - 15 + XDS[6] + 20) / 2 - textwidth(ThemDauSach) / 2, 15, HieuChinhDauSach);

	settextstyle(BOLD_FONT, HORIZ_DIR, 2);
	setcolor(TEXT_TITLE_COLOR);
	setbkcolor(BG_HOME_COLOR);
	outtextxy(XDS[6] + 60, 470 - textheight(ThongBao) / 2, ThongBao);

	setfillstyle(SOLID_FILL, BG_HOME_COLOR);
	outtextxy(XDS[6] + 20 + 60 + textwidth(ThongBao), 470 - textheight(ThongBao) / 2, mess);

	edHieuChinhISBN.draw();
	edHieuChinhTenSach.draw();
	edHieuChinhSoTrang.draw();
	edHieuChinhTacGia.draw();
	edHieuChinhNXB.draw();
	edHieuChinhTheLoai.draw();

	btnBackToThemDauSach.draw();
	btnHieuChinhDauSach.draw();
}

void DrawHieuChinhDauSachDone(){
	btnBackToThemDauSach.draw();
} 
// cac ham xoa cac chu chim
void ClearContentThemSach() {
	memset(edThemMaSach.content, 0, sizeof(edThemMaSach.content));
	memset(edThemTrangThaiSach.content, 0, sizeof(edThemTrangThaiSach.content));
}

void ClearContentHieuChinhSach() {
	memset(edHieuChinhMaSach.content, 0, sizeof(edHieuChinhMaSach.content));
	memset(edHieuChinhTrangThaiSach.content, 0, sizeof(edHieuChinhTrangThaiSach.content));
	memset(edHieuChinhViTriSach.content, 0, sizeof(edHieuChinhViTriSach.content));
}

void ClearContentNhapSoLuongSach() {
	memset(edNhapSoLuongSach.content, 0, sizeof(edNhapSoLuongSach.content));
}

void ClearContentThemDauSach() {
	memset(edThemISBN.content, 0, sizeof(edThemISBN.content));
	memset(edThemTenSach.content, 0, sizeof(edThemTenSach.content));
	memset(edThemSoTrang.content, 0, sizeof(edThemSoTrang.content));
	memset(edThemTacGia.content, 0, sizeof(edThemTacGia.content));
	memset(edThemNXB.content, 0, sizeof(edThemNXB.content));
	memset(edThemTheLoai.content, 0, sizeof(edThemTheLoai.content));
}
void ClearContentHieuChinhDauSach() {
	memset(edHieuChinhISBN.content, 0, sizeof(edHieuChinhISBN.content));
	memset(edHieuChinhTenSach.content, 0, sizeof(edHieuChinhTenSach.content));
	memset(edHieuChinhSoTrang.content, 0, sizeof(edHieuChinhSoTrang.content));
	memset(edHieuChinhTacGia.content, 0, sizeof(edHieuChinhTacGia.content));
	memset(edHieuChinhNXB.content, 0, sizeof(edHieuChinhNXB.content));
	memset(edHieuChinhTheLoai.content, 0, sizeof(edHieuChinhTheLoai.content));
}


//========================= thuat toan tao ma sach tu dung ===================
void AutoCreateMaSach() {
	if (curNhapSach == 1) startIndexSach = DSDS.nodes[curDauSach]->soluong;
	else startIndexSach++;

	char id[20];
	sprintf(id, "%s-%d", DSDS.nodes[curDauSach]->ISBN, startIndexSach);
	strcpy(edThemMaSach.content, id);
}
//====================================================
// check cac truong  hop neu chua nhap thi nhap vo k dc bo trong
bool CheckSach() {
	if (strlen(edThemTrangThaiSach.content) == 0 ||
		strlen(edThemViTriSach.content) == 0) {

		strcpy(mess, "=> Khong duoc bo trong bat ki truong nao");
		return false;
	}
	if (edThemTrangThaiSach.toInt() == 1) {
		strcpy(mess, "=>TT sach ban dau khong the la DA CHO MUON");
		return false;
	}
	return true;
}

bool CheckHieuChinhSach() {
	if (strlen(edHieuChinhTrangThaiSach.content) == 0 ||
		strlen(edHieuChinhViTriSach.content) == 0) {

		strcpy(mess, "=> Khong duoc bo trong bat ki truong nao");
		return false;
	}
	if (canEditTrangThai && edHieuChinhTrangThaiSach.toInt() == 1) {
		strcpy(mess, "=> Trang thai sach khong the la: DA CHO MUON");
		return false;
	}
	return true;
}


//int CheckSoLuongSach() {
//	int l=atoi(edNhapSoLuongSach.content);
//	if(l<99){
//		return l;
//	}else if(l>=99){
//		return 99;
//	}else{
//		strcpy(mess, "Hay nhap so luong sach them");
//	}
//	
//}
bool CheckSoLuongSach() {
//	itoa(CheckSoLuongSach(),edNhapSoLuongSach.content , 10);
	if (strlen(edNhapSoLuongSach.content) == 0) {
		strcpy(mess, "Hay nhap so luong sach them");
		return false;
	}
	
	return true;
}


bool CheckDauSachXoa(){
	if(DSDS.nodes[curDauSach]->First!=NULL){
		strcpy(mess, "=> DAU SACH NAY DA CO SACH, KHONG THE XOA!");
		setfillstyle(SOLID_FILL, BG_HOME_COLOR);
		outtextxy(40,690, mess);
		return false;
	}
	return true;
}
bool CheckDauSach() {
	if (strlen(edThemISBN.content) == 0) {
		strcpy(mess, "ISBN khong duoc bo trong");
		Edit = &edThemISBN;
		Edit->draw();
		return false;
	}
	else if (strlen(edThemTenSach.content) == 0) {
		strcpy(mess, "Ten sach khong duoc bo trong");
		Edit = &edThemTenSach;
		Edit->draw();
		return false;
	}
	else if (strlen(edThemSoTrang.content) == 0) {
		strcpy(mess, "So trang khong duoc bo trong");
		Edit = &edThemSoTrang;
		Edit->draw();
		return false;
	}
	else if (strlen(edThemTacGia.content) == 0) {
		strcpy(mess, "Tac gia khong duoc bo trong");
		Edit = &edThemTacGia;
		Edit->draw();
		return false;
	}
	else if (strlen(edThemNXB.content) == 0) {
		strcpy(mess, "NXB khong duoc bo trong");
		Edit = &edThemNXB;
		Edit->draw();
		return false;
	}
	else if (strlen(edThemTheLoai.content) == 0) {
		strcpy(mess, "The loai khong duoc bo trong");
		Edit = &edThemTheLoai;
		Edit->draw();
		return false;
	}

	if (ExistsDauSach(DSDS, edThemISBN.content) != -1) {
		strcpy(mess, "ISBN da ton tai");
		Edit = &edThemISBN;
		Edit->draw();
		return false;
	}
// da hieu roi ne
	char chDate[11];
	strcpy(chDate, GetSystemDate());
	int* d = SplitDate(chDate);
	int year = d[2];
	delete[] d;
	int y = edThemNXB.toInt();
	if (y > year) {
		strcpy(mess, "NXB khong the lon hon nam hien tai");
		Edit = &edThemNXB;
		Edit->draw();
		return false;
	}

	return true;
}

bool CheckHieuChinhDauSach() {
	if (strlen(edHieuChinhISBN.content) == 0) {
		strcpy(mess, "ISBN khong duoc bo trong");
		Edit = &edHieuChinhISBN;
		Edit->draw();
		return false;
	}
	else if (strlen(edHieuChinhTenSach.content) == 0) {
		strcpy(mess, "Ten sach khong duoc bo trong");
		Edit = &edHieuChinhTenSach;
		Edit->draw();
		return false;
	}
	else if (strlen(edHieuChinhSoTrang.content) == 0) {
		strcpy(mess, "So trang khong duoc bo trong");
		Edit = &edHieuChinhSoTrang;
		Edit->draw();
		return false;
	}
	else if (strlen(edHieuChinhTacGia.content) == 0) {
		strcpy(mess, "Tac gia khong duoc bo trong");
		Edit = &edHieuChinhTacGia;
		Edit->draw();
		return false;
	}
	else if (strlen(edHieuChinhNXB.content) == 0) {
		strcpy(mess, "NXB khong duoc bo trong");
		Edit = &edHieuChinhNXB;
		Edit->draw();
		return false;
	}
	else if (strlen(edHieuChinhTheLoai.content) == 0) {
		strcpy(mess, "The loai khong duoc bo trong");
		Edit = &edHieuChinhTheLoai;
		Edit->draw();
		return false;
	}
// da hieu roi
	char chDate[11];
	strcpy(chDate, GetSystemDate());
	int* d = SplitDate(chDate);
	int year = d[2];
	delete[] d;
	int y = edHieuChinhNXB.toInt();
	if (y > year) {
		strcpy(mess, "NXB khong the lon hon nam hien tai");
		Edit = &edHieuChinhNXB;
		Edit->draw();
		return false;
	}

	return true;
}


//lay hieu chinh dau sach
void GetHieuChinhDauSach(int i) {
	curDauSach = i;
	ClearContentHieuChinhDauSach();

	char ch[10];
	strcpy(edHieuChinhISBN.content, DSDS.nodes[i]->ISBN);
	strcpy(edHieuChinhTenSach.content, DSDS.nodes[i]->tensach);
	itoa(DSDS.nodes[i]->sotrang, ch, 10);//10 la he so
	strcpy(edHieuChinhSoTrang.content, ch);
	strcpy(edHieuChinhTacGia.content, DSDS.nodes[i]->tacgia);
	itoa(DSDS.nodes[i]->nxb, ch, 10);
	strcpy(edHieuChinhNXB.content, ch);
	strcpy(edHieuChinhTheLoai.content, DSDS.nodes[i]->theloai);

	ClearRightLayout();
	DrawHieuChinhDauSach();
}
// tiet muc hay da toi roi
void DauSachEvent() {
	
	ItemEvent();//ham nay lam sau di

	ButtonEffect(btnQuayVe);//MENU
	ButtonEffect(btnClearTimDauSach);//CLEAR tim

	ButtonEffect(btnPrevDauSach);//<<
	ButtonEffect(btnNextDauSach);//>>
	
	ButtonEffect(btnFirstDauSach);//FIRST
	ButtonEffect(btnLastDauSach);//LAST
	


	if (Window == THEM_DAU_SACH) {
		ButtonEffect(btnThemDauSach);//THEM
		
	}
	else if (Window == HIEU_CHINH_DAU_SACH) {
		ButtonEffect(btnHieuChinhDauSach);//HIEU CHINH
		ButtonEffect(btnBackToThemDauSach);//HUY
	}
	//TIET MUC LAM TA DAU CA DAU 
	else if (Window == DANH_MUC_SACH) {
		ButtonEffect(btnBackToThemDauSach);//HUY
		ButtonEffect(btnPrevDanhMucSach);//<<
		ButtonEffect(btnNextDanhMucSach);//>>
	//	ButtonEffect(btnXoasachnhapdu);//XOA SACH
		ButtonEffect(btnXoaDAUSACH);// XOA DAU SACH
		if (subWindow == NHAP_SACH) {
			ButtonEffect(btnNhapSoLuongSach);//NHAP
		}
		else if (subWindow == THEM_SACH) {
			ButtonEffect(btnThemSach);//THEM
		}
		else if (subWindow == HIEU_CHINH_SACH) {
			ButtonEffect(btnHieuChinhSach);//EDIT
			ButtonEffect(btnBackToNhapSach);//BACK
		}
	}else if (subWindow == XOA_DAU_SACH_DONE) {
		ButtonEffect(btnBackToThemDauSach);//HUY
	}
	
		//PHAN BAT SU KIEN NE PHAN KHO NHAT NE
	// Su kien Click chuot trai 
	if (GetAsyncKeyState(VK_LBUTTON)) {
		ItemLeftMouseClick();

		if (Edit != NULL) {
			int n = strlen(Edit->content);
			Edit->content[n] = ' ';
			Edit->draw();
			Edit->content[n] = '\0';
		}

		if (curMenu == btnQLDauSach.id) {

			if (edTimDauSach.isMouseHover(mx, my)) {
				Edit = &edTimDauSach;
			}
			
			else if (btnPrevDauSach.isMouseHover(mx, my)) {
				if (curPageDauSach > 1) {
					--curPageDauSach;
					ClearLayoutListDauSach();
					DrawList();
				}
			}
			else if (btnNextDauSach.isMouseHover(mx, my)) {
				if (curPageDauSach < totalPageDauSach) {
					++curPageDauSach;
					ClearLayoutListDauSach();
					DrawList();
				}
			}
			
			else if (btnFirstDauSach.isMouseHover(mx, my)) {
				if (curPageDauSach > 1) {
					curPageDauSach = 1;
					ClearLayoutListDauSach();
					DrawList();
				}
			}
			
			else if (btnLastDauSach.isMouseHover(mx, my)) {
				if (curPageDauSach < totalPageDauSach) {
					curPageDauSach = totalPageDauSach;
					ClearLayoutListDauSach();
					DrawList();
				}
			}
			
			else if (btnClearTimDauSach.isMouseHover(mx, my)) {
				memset(edTimDauSach.content, 0, sizeof(edTimDauSach.content));
				edTimDauSach.draw();
				DrawList();
			}
			// man hinh Them dau sach
			if (Window == THEM_DAU_SACH) {

				if (btnThemDauSach.isMouseHover(mx, my)) {
					// Them dau sach
					// check truoc khi add
					if (CheckDauSach()) {
						DauSach* dausach = new DauSach(edThemISBN.trim(),
							edThemTenSach.trim(),
							edThemSoTrang.toInt(),
							edThemTacGia.trim(),
							edThemNXB.toInt(),
							edThemTheLoai.trim());

						AddDauSach(DSDS, dausach);
						ClearLayoutListDauSach();

						if (strlen(edTimDauSach.content) > 0) {
							GetListNodes(DSDS, edTimDauSach.content, sizeListIndexDauSachSearch);//cautrucdausach.h
						}

						DrawList();
						ClearContentThemDauSach();
						strcpy(mess, "Them dau sach thanh cong!");
					}
					DrawThemDauSach();
				}

				if (edThemISBN.isMouseHover(mx, my)) {
					Edit = &edThemISBN;
				}
				else if (edThemTenSach.isMouseHover(mx, my)) {
					Edit = &edThemTenSach;
				}
				else if (edThemSoTrang.isMouseHover(mx, my)) {
					Edit = &edThemSoTrang;
				}
				else if (edThemTacGia.isMouseHover(mx, my)) {
					Edit = &edThemTacGia;
				}
				else if (edThemNXB.isMouseHover(mx, my)) {
					Edit = &edThemNXB;
				}
				else if (edThemTheLoai.isMouseHover(mx, my)) {
					Edit = &edThemTheLoai;
				}


			}
			else if (Window == HIEU_CHINH_DAU_SACH) {
				if (btnHieuChinhDauSach.isMouseHover(mx, my)) {
					// Hieu chinh dau sach
					if (CheckHieuChinhDauSach()) {
						DauSach* dausach = new DauSach(edHieuChinhISBN.content,
							edHieuChinhTenSach.trim(),
							edHieuChinhSoTrang.toInt(),
							edHieuChinhTacGia.trim(),
							edHieuChinhNXB.toInt(),
							edHieuChinhTheLoai.trim());
						UpdateDauSach(DSDS, dausach, curDauSach);//hieu chinh
						ClearLayoutListDauSach();

						if (strlen(edTimDauSach.content) > 0) {
							GetListNodes(DSDS, edTimDauSach.content, sizeListIndexDauSachSearch);
						}

						DrawList();
					//	ClearContentHieuChinhDauSach();
						curDauSach = -1;
						strcpy(mess, "Hieu chinh dau sach thanh cong!");
						Window=HIEU_CHINH_DAU_SACH_DONE;
						
					}
					
					
					DrawHieuChinhDauSach();
				    DrawHieuChinhDauSachDone();
				}
				// if()

				if (curDauSach != -1) {// khac -1 chuaw hieu chinh
					if (edHieuChinhISBN.isMouseHover(mx, my)) {
						// khong cho phep chinh sua ISBN
//						Edit = &edHieuChinhISBN;
					}
					else if (edHieuChinhTenSach.isMouseHover(mx, my)) {
						Edit = &edHieuChinhTenSach;
					}
					else if (edHieuChinhSoTrang.isMouseHover(mx, my)) {
						Edit = &edHieuChinhSoTrang;
					}
					else if (edHieuChinhTacGia.isMouseHover(mx, my)) {
						Edit = &edHieuChinhTacGia;
					}
					else if (edHieuChinhNXB.isMouseHover(mx, my)) {
						Edit = &edHieuChinhNXB;
					}
					else if (edHieuChinhTheLoai.isMouseHover(mx, my)) {
						Edit = &edHieuChinhTheLoai;
					}
				}


			}
			
			else if (Window == DANH_MUC_SACH) {
				if (btnPrevDanhMucSach.isMouseHover(mx, my)) {
					if (curPageSach > 1) {
						--curPageSach;
						ClearLayoutDanhMucSach();
						DrawDanhMucSach();
					}
				}
				
				
				else if (btnNextDanhMucSach.isMouseHover(mx, my)) {
					if (curPageSach < totalPageSach) {
						++curPageSach;
						ClearLayoutDanhMucSach();
						DrawDanhMucSach();
					}
				}
				else if (btnXoaDAUSACH.isMouseHover(mx, my)) {
					if (DSDS.nodes[curDauSach]->soluong==0) {
						DeleteDauSach(DSDS,DSDS.nodes[curDauSach]->tensach);
						ClearLayoutDanhMucSach();
						
						//DrawThemDauSach();
						Window = XOA_DAU_SACH_DONE;
						ClearRightLayout();
						DrawXoaDauSachDone();
						setcolor(TIPS);
				        outtextxy(XDMS[0]+20,400, "=> XOA DAU SACH THANH CONG!");
				        
				        ClearLayoutListDauSach();
						DrawList();
					}else{
						setcolor(TIPS);
						strcpy(mess,"=> DAU SACH DA CO SACH, KHONG THE XOA!");
				      
				        outtextxy(XDMS[0]+20,390, mess);
					}
				}
//				else if (btnXoasachnhapdu.isMouseHover(mx, my)) {
//					if (DSDS.nodes[curDauSach]->soluong!=0) {
//						
//						
//							DeleteSachLast(DSDS.nodes[curDauSach]->First);
//						
//							
//							DSDS.nodes[curDauSach]->soluong--;
//			
//							ClearLayoutDanhMucSach();
//						    DrawDanhMucSach();
//						}
//				}

				if (subWindow == NHAP_SACH) {
					if (btnNhapSoLuongSach.isMouseHover(mx, my)) {
						if (CheckSoLuongSach()) {
							
							totalNhapSach = edNhapSoLuongSach.toInt();
							curNhapSach = 1;
							subWindow = THEM_SACH;
							memset(edThemViTriSach.content, 0, sizeof(edThemViTriSach.content));
							strcpy(mess, "");
							DrawThemSach();
						}
					}

					if (edNhapSoLuongSach.isMouseHover(mx, my)) {
						Edit = &edNhapSoLuongSach;
					}

				}
				//DOC LAI CAI QQ NAY CHO KY
				else if (subWindow == THEM_SACH) {
					if (btnThemSach.isMouseHover(mx, my)) {
						// Check them sach
						if (CheckSach()) {//check la kiem tra k dc bo trong
							Sach sach(edThemMaSach.content, edThemTrangThaiSach.toInt(), edThemViTriSach.content);
							
							InsertLast_NodeSach(DSDS.nodes[curDauSach]->First, sach);
							//cout<<"\nGia tri cua sach them la: "<<DSDS.nodes[curDauSach]->First->sach.MASACH;
		
							DSDS.nodes[curDauSach]->soluong++;
							//				printf("So luong: %d \n", DSDS.nodes[curDauSach]->soluong);

							ClearContentThemSach();
							ClearRightLayout();
							++curNhapSach;

							strcpy(mess, "=>Them sach thanh cong!");
							DrawThemSach();

							if (curNhapSach > totalNhapSach) {//sau khi nhap xong
								ClearContentNhapSoLuongSach();
								subWindow = NHAP_SACH;
								curNhapSach = -1;
								totalNhapSach = 0;
								DrawNhapSach();
							}

						}
						else {
							DrawThemSach();
						}

						DrawDanhMucSach();
					}

					if (edThemTrangThaiSach.isMouseHover(mx, my)) {
						Edit = &edThemTrangThaiSach;
					}
					else if (edThemViTriSach.isMouseHover(mx, my)) {
						Edit = &edThemViTriSach;
					}

				}
				else if (subWindow == HIEU_CHINH_SACH) {
					if (btnHieuChinhSach.isMouseHover(mx, my)) {
						if (CheckHieuChinhSach()) {
							// update
							NodeSach* nodeSelect = GetNodeSach(DSDS.nodes[curDauSach]->First, 4 * (curPageSach - 1) + curSach);
						
							Sach sach(edHieuChinhMaSach.content, edHieuChinhTrangThaiSach.toInt(), edHieuChinhViTriSach.content);
						//tao ra mot sach moi co noi dung da hieu chinh
							UpdateNodeSach(nodeSelect, sach);
							ClearRightLayout();
							strcpy(mess, "=> Hieu chinh sach thanh cong!");
							DrawDanhMucSach();
						}
						DrawHieuChinhSach();
					}
					else if (btnBackToNhapSach.isMouseHover(mx, my)) {
						subWindow = NHAP_SACH;
						DrawNhapSach();
					}


					if (edHieuChinhTrangThaiSach.isMouseHover(mx, my) && canEditTrangThai) {
						Edit = &edHieuChinhTrangThaiSach;
					}
					else if (edHieuChinhViTriSach.isMouseHover(mx, my)) {
						Edit = &edHieuChinhViTriSach;
					}
				}

			}
		}

		if (btnBackToThemDauSach.isMouseHover(mx, my)) {
			Window = THEM_DAU_SACH;
			ClearRightLayout();
			ClearContentThemDauSach();
			strcpy(mess, "");
			DrawThemDauSach();
		}
		else if (btnQuayVe.isMouseHover(mx, my)) {
			SetMenuSelect(0);
		}
		else if (btnQLSach.isMouseHover(mx, my)) {

		}
		else if (btnThongTin.isMouseHover(mx, my)) {

		}
		else if (btnThoat.isMouseHover(mx, my)) {

		}
	}
	else if (GetAsyncKeyState(VK_RBUTTON)) {
		ItemRightMouseClick();
	}

}

void ItemLeftMouseClick() {
	if (curItem != -1) {
		Window = HIEU_CHINH_DAU_SACH;
		strcpy(mess, "");                //GETHIEUCHINH LA lay phan da co chu copy qua
		if (strlen(edTimDauSach.content) == 0) GetHieuChinhDauSach(10 * (curPageDauSach - 1) + curItem);
		else GetHieuChinhDauSach(listIndexDauSachSearch[10 * (curPageDauSach - 1) + curItem]);
	}
	if (Window == DANH_MUC_SACH) {
		if (curItemSach != -1) {
			subWindow = HIEU_CHINH_SACH;
			curSach = curItemSach;
		//	cout<<"\n cur sach ne: "<<curSach;
			strcpy(mess, "");

			ClearContentHieuChinhSach();

			NodeSach* nodeSelect = GetNodeSach(DSDS.nodes[curDauSach]->First, 4 * (curPageSach - 1) + curSach);
			strcpy(edHieuChinhMaSach.content, nodeSelect->sach.MASACH);
			char ch[2];
			itoa(nodeSelect->sach.trangthai, ch, 10);
			strcpy(edHieuChinhTrangThaiSach.content, ch);
			strcpy(edHieuChinhViTriSach.content, nodeSelect->sach.vitri);

			if (nodeSelect->sach.trangthai == 0) {
				canEditTrangThai = true;
			}
			else {
				canEditTrangThai = false;
			}

			DrawHieuChinhSach();
		}
	}
}

void ItemRightMouseClick() {
	if (curItem != -1) {
		Window = DANH_MUC_SACH;
		subWindow = NHAP_SACH;
		Edit = NULL;

		if (strlen(edTimDauSach.content) == 0) curDauSach = 10 * (curPageDauSach - 1) + curItem;
		else curDauSach = listIndexDauSachSearch[10 * (curPageDauSach - 1) + curItem];

		curPageSach = 1;
		Edit = NULL;
		memset(mess, 0, sizeof(mess));
		ClearRightLayout();
		ClearContentNhapSoLuongSach();
		AutoCreateMaSach();
		DrawDanhMucSach();
		DrawNhapSach();
	}
}
//THANH SANG
// co sua qua roi
void ItemEvent() {
	if (mx > XDS[0] && mx < XDS[6] && my > 180 - 8 && my < 180 + 10 * 30 - 8) {

		if (curItem != GetItemPosition(my)) {
			if (curItem != -1) {
				// khoi phuc item
				setfillstyle(SOLID_FILL, BG_COLOR);
				bar(XDS[0], 180 + curItem * 30 - 8, XDS[6], 180 + (curItem + 1) * 30);//230->180 40->30

				setbkcolor(BG_COLOR);
				settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 2);
				setcolor(TEXT_TITLE);

				if (strlen(edTimDauSach.content) == 0) {
					DrawItemDauSach((curPageDauSach - 1) * 10 + curItem, -1);
				}
				else {
					DrawItemDauSach(listIndexDauSachSearch[(curPageDauSach - 1) * 10 + curItem], curItem);
				}

				DrawBorderList();
			}

			// Ve item hien tai
			curItem = GetItemPosition(my);
			if (curItem != -1) {
				setfillstyle(SOLID_FILL, LINE);
				bar(XDS[0], 180 + curItem * 30 - 8, XDS[6], 180 + (curItem + 1) * 30);

				settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 2);
				setbkcolor(LINE);
				setcolor(BG_EDITTEXT_COLOR);

				if (strlen(edTimDauSach.content) == 0) {
					DrawItemDauSach((curPageDauSach - 1) * 10 + curItem, -1);
				}
				else {
					DrawItemDauSach(listIndexDauSachSearch[(curPageDauSach - 1) * 10 + curItem], curItem);
				}

				DrawBorderList();
			}
		}
	}
	else {
		if (curItem != -1) {
			// khoi phuc item
			setfillstyle(SOLID_FILL, BG_COLOR);
			bar(XDS[0], 180 + curItem * 30 - 8, XDS[6], 180 + (curItem + 1) * 30);
			setbkcolor(BG_COLOR);
			settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 2);
			setcolor(TEXT_TITLE);

			if (strlen(edTimDauSach.content) == 0) {
				DrawItemDauSach((curPageDauSach - 1) * 10 + curItem, -1);
			}
			else {
				DrawItemDauSach(listIndexDauSachSearch[(curPageDauSach - 1) * 10 + curItem], curItem);
			}

			DrawBorderList();
			curItem = -1;
		}
	}

	// important
	if (Window != DANH_MUC_SACH) return;

	//if(mx > XDMS[0] && mx < XDMS[3] && my > 140-8 && my < 140+10*40-8){
	if (mx > XDMS[0] && mx < XDMS[3] && my > 140 - 8 && my < 140 + 4 * 40 - 8) {
		// khoi phuc item
		if (curItemSach != GetItemSachPosition(my)) {
			if (curItemSach != -1) {
				setfillstyle(SOLID_FILL, BG_COLOR);
				bar(XDMS[0], 140 + curItemSach * 40 - 8, XDMS[3], 140 + (curItemSach + 1) * 40 - 8);

				setbkcolor(BG_COLOR);
				settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 2);
				setcolor(TEXT_TITLE);

				DrawBorderListSach();
				DrawItemSach(GetNodeSach(DSDS.nodes[curDauSach]->First, 4 * (curPageSach - 1) + curItemSach)->sach, curItemSach);//5
			}

			// Ve item hien tai
			curItemSach = GetItemSachPosition(my);
			if (curItemSach != -1) {
				setfillstyle(SOLID_FILL, LINE);
				bar(XDMS[0], 140 + curItemSach * 40 - 8, XDMS[3], 140 + (curItemSach + 1) * 40 - 8);

				settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 2);
				setbkcolor(LINE);
				setcolor(BG_EDITTEXT_COLOR);
				DrawItemSach(GetNodeSach(DSDS.nodes[curDauSach]->First, 4 * (curPageSach - 1) + curItemSach)->sach, curItemSach);
				DrawBorderListSach();
			}
		}
	}
	else {
		if (curItemSach != -1) {
			// khoi phuc item
			setfillstyle(SOLID_FILL, BG_COLOR);
			bar(XDMS[0], 140 + curItemSach * 40 - 8, XDMS[3], 140 + (curItemSach + 1) * 40 - 8);

			setbkcolor(BG_COLOR);
			settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 2);
			setcolor(TEXT_TITLE);
			DrawItemSach(GetNodeSach(DSDS.nodes[curDauSach]->First, 4 * (curPageSach - 1) + curItemSach)->sach, curItemSach);
			DrawBorderListSach();
			curItemSach = -1;
		}
	}
}

int GetItemPosition(int y) {
	//int pos = (y-230+8)/40;
	int pos = (y - 180 + 8) / 30;
	int i = 10 * (curPageDauSach - 1) + pos;
	if (strlen(edTimDauSach.content) == 0) {
		if (i >= DSDS.n) return -1;
	}
	else {
		if (i >= sizeListIndexDauSachSearch) return -1;
	}
	return pos;
}

int GetItemSachPosition(int y) {
	int pos = (y - 140 + 8) / 40;
	//int i = 10*(curPageSach-1) + pos;
	int i = 4 * (curPageSach - 1) + pos;
	if (i >= DSDS.nodes[curDauSach]->soluong) return -1;
	else return pos;
}


void ClearLayoutListDauSach() {
	setfillstyle(SOLID_FILL, BG_COLOR);
	bar(XDS[0], 150, XDS[6], 500);
}
//da sua
void ClearLayoutSach() {
	setfillstyle(SOLID_FILL, BG_COLOR);
	//	bar(XDMS[0]-2, 610, w, 880);
	//bar(XDMS[0] - 2, 390, w, 738);
	bar(XDS[6]+20, 380, 1525, 728);
}

void ClearLayoutDanhMucSach() {
	setfillstyle(SOLID_FILL, BG_COLOR);
	bar(XDMS[0] -2, 70, 1525, 390);
}
// VE BANG 6 COT CUA DANH SACH DAU SACH 
void DrawBorderList() {
	setlinestyle(SOLID_LINE, 0, 3);//3 kieu duong mau to do dam
	setcolor(TEXT_TITLE);
	rectangle(XDS[0], 130, XDS[6], 480);//750
	line(XDS[0], 140 + 15 + 2 * 9, XDS[6], 140 + 15 + 2 * 9);//20
	for (int i = 0; i < 6; i++) {
		line(XDS[i + 1], 130, XDS[i + 1], 480);//750
	}
}





// CAI NAY CUA DANH MUC SACH
void DrawBorderListSach() {
	setlinestyle(SOLID_LINE, 0, 3);
	setcolor(TEXT_TITLE);// mau vien nha
	//rectangle(XDMS[0], 70, XDMS[3], 400);//ve cai bang 3 cot 2 dong
	rectangle(XDMS[0], 70, XDMS[3], 290);
	line(XDMS[0], 132, XDMS[3], 132);//
	line(XDMS[1], 70, XDMS[1], 290);
	line(XDMS[2], 70, XDMS[2], 290);
}
// CAI BANG TO NHAT KHUNG  DANH SACH DAU SACH
void DrawList() {
	ClearLayoutListDauSach();
	DrawBorderList();
	char ch[6][20] = { "ISBN", "Ten sach", "So trang", "Tac gia", "NXB", "The loai" };

	settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 1);
	setcolor(BORDER_COLOR);
	setbkcolor(BG_COLOR);
	for (int i = 0; i < 6; i++) {
		outtextxy(XDS[i] + (XDS[i + 1] - XDS[i]) / 2 - textwidth(ch[i]) / 2, 140, ch[i]);//170
	}

	// caculate Total Page 
	// Num per page = 13

//phan trang
	setcolor(TEXT_TITLE);
	if (strlen(edTimDauSach.content) == 0) {// k có tim dau sach thi ve nhu binh thuong ne
		totalPageDauSach = (DSDS.n - 1) / 10 + 1;
		for (int i = 10 * (curPageDauSach - 1); i < 10 * curPageDauSach; i++) {
			if (i >= DSDS.n) break;
			DrawItemDauSach(i, -1);
		}
	}// co tim dau sach
	else {
		totalPageDauSach = (sizeListIndexDauSachSearch - 1) / 10 + 1;
		int j = 0;
		for (int i = 10 * (curPageDauSach - 1); i < 10 * curPageDauSach; i++) {
			if (i >= sizeListIndexDauSachSearch) break;
			DrawItemDauSach(listIndexDauSachSearch[i], j++);
		}
	}

	// num page
	settextstyle(BOLD_FONT, HORIZ_DIR, 2);
	char chPage[20];
	sprintf(chPage, "%d / %d", curPageDauSach, totalPageDauSach);
	outtextxy((XDS[0] + XDS[6]) / 2 - textwidth(chPage) / 2, 515, chPage);//785->600

	// tips
//	setcolor(TIPS);
//	rectangle(XDS[0], 730, XDS[6], 785);
//	outtextxy(30, 740, "Click chuot trai: Hieu chinh dau sach");
//	outtextxy(30, 760, "Click chuot phai: Xem thong tin, danh muc sach");
	setcolor(TIPS);
	rectangle(XDS[0], 670, XDS[6], 770);
	outtextxy(30, 690, " ________________________Huong dan su dung________________________");
	outtextxy(30, 720, " * Click chuot trai: Hieu chinh dau sach ");
	outtextxy(30, 740, " * Click chuot phai: Xem thong tin, danh muc sach");
}
//da chinh chu trong khung len duoc cao hon r
   //da co sua
void DrawItemDauSach(int i, int j) {
	char chs[10];
	settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 1);
	outtextxy(XDS[0] + 5, 180 + (j != -1 ? j : (i % 10)) * 30, DSDS.nodes[i]->ISBN);//230->180
	outtextxy(XDS[1] + 5, 180 + (j != -1 ? j : (i % 10)) * 30, DSDS.nodes[i]->tensach);//*40->30
	if (DSDS.nodes[i]->sotrang > 0) {
		itoa(DSDS.nodes[i]->sotrang, chs, 10);
		outtextxy(XDS[2] + 10, 180 + (j != -1 ? j : (i % 10)) * 30, chs);
	}
	outtextxy(XDS[3] + 5, 180 + (j != -1 ? j : (i % 10)) * 30, DSDS.nodes[i]->tacgia);
	if (DSDS.nodes[i]->nxb > 0) {
		itoa(DSDS.nodes[i]->nxb, chs, 10);
		outtextxy(XDS[4] + 10, 180 + (j != -1 ? j : (i % 10)) * 30, chs);
	}
	outtextxy(XDS[5] + 5, 180 + (j != -1 ? j : (i % 10)) * 30, DSDS.nodes[i]->theloai);
}
//DANH MUC SACH
// da co xua i thanh i*4 
void DrawItemSach(Sach& sach, int i) {
	outtextxy(XDMS[0] + 30, 140 + (i % 4) * 40, sach.MASACH);
	outtextxy(XDMS[1] + 30, 140 + (i % 4) * 40, TrangThaiSach[sach.trangthai]);
	outtextxy(XDMS[2] + 30, 140 + (i % 4) * 40, sach.vitri);
}

void DrawXoaDauSachDone() {
	btnBackToThemDauSach.draw();
}
