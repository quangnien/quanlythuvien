struct SachMT {
	char MASACH[20];
	char TenSach[30];
	char NgayMuon[10]; 
	int TrangThai;  
}; 

struct DSMuonTra { 
	int n;
	SachMT* mt = new SachMT[3]; //max = 3 SMT

	DSMuonTra() {
		n = 0; 
	}
	~DSMuonTra() {
		delete[] mt;
	}
};

DSMuonTra DSMT;

void RunMuonTra() {
	DrawBorderMuonTra();

	curMenuMuonTra = -1;
	btnMuonSach.isHover = true;
	btnMuonSach.isChoose = true;
	SetMenuMuonTraSelect(btnMuonSach.id);

	btnBackToMenu.draw();
	btnMuonSach.draw();
	btnTraSach.draw();
	btnTopTen.draw();
	//btnCacSachQuaHan.draw();
}

void MuonTraEvent() {
	if (curDGMT != NULL && curMenuMuonTra != btnTopTen.id) ItemMTEvent(); //&& curMenuMuonTra != btnCacSachQuaHan.id

	ButtonEffect(btnBackToMenu);
	ButtonEffect(btnMuonSach);
	ButtonEffect(btnTraSach);
	ButtonEffect(btnTopTen);
	//ButtonEffect(btnCacSachQuaHan);

	if (curMenuMuonTra == btnMuonSach.id) {
		ButtonEffect(btnTimMaDG);
		if (curDGMT != NULL) ButtonEffect(btnTimMaSach);
		if (canMT) ButtonEffect(btnXacNhanMuonSach);
	}
	else if (curMenuMuonTra == btnTraSach.id) {
		ButtonEffect(btnTimMaDG);
		if (curMT != -1) {
			if (subWindow == XAC_NHAN_TRA_SACH) {
				ButtonEffect(btnXacNhanTraSach);
				ButtonEffect(btnLamMatSach);
			}
			else if (subWindow == XAC_NHAN_LAM_MAT_SACH) {
				ButtonEffect(btnXacNhanLamMatSach);
				ButtonEffect(btnHuyLamMatSach);
			}

		}
	}
	else if (curMenuMuonTra == btnTopTen.id) {

	}
	//	else if(curMenuMuonTra == btnCacSachQuaHan.id){
	//		
	//	}

	if (GetAsyncKeyState(VK_LBUTTON)) {
		if (curMenuMuonTra == btnTraSach.id) ItemMTClick();

		if (btnBackToMenu.isMouseHover(mx, my)) {
			SetMenuSelect(0);
		}
		else if (btnMuonSach.isMouseHover(mx, my)) {
			SetMenuMuonTraSelect(btnMuonSach.id);
		}
		else if (btnTraSach.isMouseHover(mx, my)) {
			SetMenuMuonTraSelect(btnTraSach.id);
		}
		else if (btnTopTen.isMouseHover(mx, my)) {
			SetMenuMuonTraSelect(btnTopTen.id);
		}
		//		else if(btnCacSachQuaHan.isMouseHover(mx, my)){
		//			SetMenuMuonTraSelect(btnCacSachQuaHan.id);
		//		}

		if (curMenuMuonTra == btnMuonSach.id) {
			if (btnTimMaDG.isMouseHover(mx, my)) {
				curDGMT = &SearchDocGia(TreeDocGia, edNhapMaDGMuonSach.toInt())->docgia;
				DrawThongTinDocGia();
			}

			if (edNhapMaDGMuonSach.isMouseHover(mx, my)) {
				Edit = &edNhapMaDGMuonSach;
			}

			if (curDGMT != NULL) {
				if (btnTimMaSach.isMouseHover(mx, my)) {
					if (strlen(edNhapMaSachMuonSach.content) > 0) {
						// tim Dau Sach co chua Ma Sach can tim
						curDSMT = GetDauSach(DSDS, edNhapMaSachMuonSach.content);
						if (curDSMT == NULL) {
							curSachMT = NULL;
						}
						else {
							// curSachMT != NULL : always
							curSachMT = GetSach(curDSMT->First, edNhapMaSachMuonSach.content);
						}

						strcpy(edNhapNgayMuonSach.content, GetSystemDate());
						DrawThongTinSach();
					}
				}
				if (edNhapMaSachMuonSach.isMouseHover(mx, my)) {
					Edit = &edNhapMaSachMuonSach;
				}
				if (curSachMT != NULL && canMT) {
					if (edNhapNgayMuonSach.isMouseHover(mx, my)) {
						Edit = &edNhapNgayMuonSach;
					}
					if (btnXacNhanMuonSach.isMouseHover(mx, my)) {
						// Muon sach
						if (!CheckDate(edNhapNgayMuonSach.content)) {
							strcpy(mess, "THONG BAO : Ngay muon khong hop le");
							DrawThongTinSach();
						}
						else if (CompareDate(edNhapNgayMuonSach.content, GetSystemDate()) > 0) {
							strcpy(mess, "THONG BAO: Ngay muon khong the muon hon ngay hien tai");
							DrawThongTinSach();
						}
						else {
							// 0: DANG MUON
							MuonTra muon(curSachMT->MASACH, edNhapNgayMuonSach.content, "", 0);
							InsertLast_MuonTra(curDGMT->mt, muon);

							NodeSach* nodeSach = GetNodeSach(curDSMT->First, curSachMT->MASACH);
							Sach sach = nodeSach->sach;
							sach.trangthai = 1; 	// DA CHO MUON
							UpdateNodeSach(nodeSach, sach);

							// Tang so luot muon sach cua Dau Sach
							curDSMT->soluotmuon++;

							curDSMT = NULL;
							curSachMT = NULL;
							canMT = false;

							memset(edNhapMaSachMuonSach.content, 0, sizeof(edNhapMaSachMuonSach.content));
							DrawThongTinDocGia();
						}
					}
				}
			}

		}
		else if (curMenuMuonTra == btnTraSach.id) {

			if (btnTimMaDG.isMouseHover(mx, my)) {
				curDGMT = &SearchDocGia(TreeDocGia, edNhapMaDGMuonSach.toInt())->docgia;
				DrawThongTinDocGia();
				setcolor(TIPS);
				
				setlinestyle(SOLID_LINE, 0, 2);
				rectangle(70 + w/2, 55, w - 20, 170);
				
				outtextxy(90 + w/2, 65, " ________________Huong dan su dung________________");
				outtextxy(90 + w/2, 100, "Click chuot trai vao tung sach trong bang sach");
				outtextxy(90 + w/2, 135, "de muon sach hoac tra sach");
			}

			if (edNhapMaDGMuonSach.isMouseHover(mx, my)) {
				Edit = &edNhapMaDGMuonSach;
			}

			if (curMT != -1 && curDGMT != NULL) {
				if (edNhapNgayTraSach.isMouseHover(mx, my)) {
					Edit = &edNhapNgayTraSach;
				}

				if (subWindow == XAC_NHAN_TRA_SACH) {
					if (btnXacNhanTraSach.isMouseHover(mx, my)) {
						if (!CheckDate(edNhapNgayTraSach.content)) {
							strcpy(mess, "THONG BAO : Ngay nhap vao khong hop le");
							DrawThongTinSachTra(curMT);
						}
						else if (CompareDate(edNhapNgayTraSach.content, DSMT.mt[curMT].NgayMuon) < 0) {
							strcpy(mess, "THONG BAO : Ngay tra sach khong the som hon ngay muon sach");
							DrawThongTinSachTra(curMT);
						}
						else if (CompareDate(edNhapNgayTraSach.content, GetSystemDate()) > 0) {
							strcpy(mess, "THONG BAO : Ngay muon khong the muon hon ngay hien tai");
							//DrawThongTinSach();
							DrawThongTinSachTra(curMT);
						}
						else {
//							if (curDGMT->trangthai == 0) {
//								curDGMT->trangthai = 1; //MO KHOA THE DOC GIA
//						        UpdateDocGia(TreeDocGia, *curDGMT);
//							}
                            //TH den sach => mo khoa the doc gia
                            int countDGbikhoa = 0;
	                    	if (curDGMT->mt.chuaTra > 0) {
		                    //	cout<<"\n__________________curDGMT->mt.chuaTra = "<<curDGMT->mt.chuaTra;
		                    	//DSMT.n = curDGMT->mt.chuaTra;
		                    	for (NodeMuonTra* mt = curDGMT->mt.First; mt != NULL; mt = mt->next) {
		                    		if (mt->muontra.trangthai == 2) {
		                    			countDGbikhoa++;
		                    		}
		                    	}
	                    	}
		                   // cout<<"\n_________________ countDGbikhoa = "<<countDGbikhoa;
	                    	if (curDGMT->trangthai == 0 && countDGbikhoa==1){
	                    		curDGMT->trangthai = 1; //MO KHOA THE DOC GIA
                                UpdateDocGia(TreeDocGia, *curDGMT);
	                    	}
	                    	
							
							// 1: DA TRA 
							MuonTra tra(DSMT.mt[curMT].MASACH, DSMT.mt[curMT].NgayMuon, edNhapNgayTraSach.content, 1);
							Update_MuonTra(curDGMT->mt, tra);

							curDSMT = GetDauSach(DSDS, DSMT.mt[curMT].MASACH);

							NodeSach* nodeSach = GetNodeSach(curDSMT->First, DSMT.mt[curMT].MASACH);
							Sach sach = nodeSach->sach;
							sach.trangthai = 0; 	// CHO MUON DUOC
							UpdateNodeSach(nodeSach, sach);

							// test
//							nodeSach = GetNodeSach(curDSMT->First, DSMT.mt[curMT].MASACH);
//							printf("TT : %d \n", nodeSach->sach.trangthai);

							curDSMT = NULL;
							curMT = -1;

							memset(edNhapNgayTraSach.content, 0, sizeof(edNhapNgayTraSach.content));
							DrawThongTinDocGia();
						}

					}
					else if (btnLamMatSach.isMouseHover(mx, my)) {
						subWindow = XAC_NHAN_LAM_MAT_SACH;
						DrawThongTinSachTra(curMT);
					}

				}
				else if (subWindow == XAC_NHAN_LAM_MAT_SACH) {
					if (btnXacNhanLamMatSach.isMouseHover(mx, my)) {
						// 2: LAM MAT
						MuonTra tra(DSMT.mt[curMT].MASACH, DSMT.mt[curMT].NgayMuon, "", 2);
						Update_MuonTra(curDGMT->mt, tra);

						curDSMT = GetDauSach(DSDS, DSMT.mt[curMT].MASACH);

						NodeSach* nodeSach = GetNodeSach(curDSMT->First, DSMT.mt[curMT].MASACH);
						Sach sach = nodeSach->sach;
						sach.trangthai = 2; 	// DA THANH LY
						UpdateNodeSach(nodeSach, sach);

						curDSMT = NULL;
						curMT = -1;

						curDGMT->trangthai = 0; // KHOA THE DOC GIA
						UpdateDocGia(TreeDocGia, *curDGMT);

						memset(edNhapNgayTraSach.content, 0, sizeof(edNhapNgayTraSach.content));
						DrawThongTinDocGia();
					}
					else if (btnHuyLamMatSach.isMouseHover(mx, my)) {
						subWindow = XAC_NHAN_TRA_SACH;
						DrawThongTinSachTra(curMT);
					}
				}

			}
		}
		else if (curMenuMuonTra == btnTopTen.id) {

		}
		//		else if(curMenuMuonTra == btnCacSachQuaHan.id){
		//			
		//		}
	}
}

void DrawBorderDSMT() {

	setcolor(TEXT_TITLE);
	setbkcolor(BG_HOME_COLOR);
	char t[4][15] = { "Ma sach", "Ten sach", "Ngay muon", "Trang thai" };
	//setfillstyle(SOLID_FILL, BORDER_COLOR);
	//settextstyle(BOLD_FONT, HORIZ_DIR, 1);
	//rectangle(XMT[0], 510, XMT[4], 725);
	setlinestyle(SOLID_LINE, 0, 3);
	setcolor(TEXT_TITLE);
	rectangle(XMT[0], 390, XMT[4], 540);
	//int yline = 580;
	int yline = 420;
	//	setcolor(TEXT_COLOR);
	line(XMT[0], yline, XMT[4], yline);
	for (int i = 0; i < 4; i++) {
		settextstyle(BOLD_FONT, HORIZ_DIR, 2);
		setcolor(TEXT_TITLE);
		line(XMT[i], 390, XMT[i], 540);
		//outtextxy((XMT[i]+XMT[i+1])/2 - textwidth(t[i])/2, (500+yline)/2-textheight(t[i])/2, t[i]);
		settextstyle(BOLD_FONT, HORIZ_DIR, 1);
		setcolor(BORDER_COLOR);
		outtextxy((XMT[i] + XMT[i + 1]) / 2 - textwidth(t[i]) / 2, (390 + yline) / 2 - textheight(t[i]) / 2, t[i]);
	}
}

void DrawBorderDSMTQuaHan() {

	setcolor(TEXT_TITLE);
	setbkcolor(BG_HOME_COLOR);
	char t[4][15] = { "Ma sach", "Ten sach", "Ngay muon", "Trang thai" };
	//setfillstyle(SOLID_FILL, BORDER_COLOR);
	//settextstyle(BOLD_FONT, HORIZ_DIR, 1);
	//rectangle(XMT[0], 510, XMT[4], 725);
	setlinestyle(SOLID_LINE, 0, 3);
	setcolor(TEXT_TITLE);
	rectangle(XMT[0], 390 + 190, XMT[4], 540 + 190);
	//int yline = 580;
	int yline = 420 + 190;
	//	setcolor(TEXT_COLOR);
	line(XMT[0], yline, XMT[4], yline);
	for (int i = 0; i < 4; i++) {
		settextstyle(BOLD_FONT, HORIZ_DIR, 2);
		setcolor(TEXT_TITLE);
		line(XMT[i], 390 + 190, XMT[i], 540 + 190);
		//outtextxy((XMT[i]+XMT[i+1])/2 - textwidth(t[i])/2, (500+yline)/2-textheight(t[i])/2, t[i]);
		settextstyle(BOLD_FONT, HORIZ_DIR, 1);
		setcolor(BORDER_COLOR);
		outtextxy((XMT[i] + XMT[i + 1]) / 2 - textwidth(t[i]) / 2, (390 + 190 + yline) / 2 - textheight(t[i]) / 2, t[i]);
	}
}

int GetItemMTPosition(int y) {
	//	int pos = (y-600+8)/40;
	int pos = (y - 425 + 5) / 40;
	if (pos >= DSMT.n) return -1;
	return pos;
}

void ItemMTClick() {
	if (curItemMT != -1) {
		subWindow = XAC_NHAN_TRA_SACH;
		strcpy(edNhapNgayTraSach.content, GetSystemDate());
		DrawThongTinSachTra(curItemMT);
	}
}

void ItemMTEvent() {
	//	if(mx > XMT[0] && mx < XMT[4] && my > 600-8 && my < 720-8){
	if (mx > XMT[0] && mx < XMT[4] && my > 425 - 5 && my < 605 - 5) {

		if (curItemMT != GetItemMTPosition(my)) {
			if (curItemMT != -1) {
				// khoi phuc item
				setfillstyle(SOLID_FILL, BG_HOME_COLOR);
				//				bar(XMT[0], 600 + curItemMT*40 - 8, XMT[4], 600+(curItemMT+1)*40-8);
				bar(XMT[0], 425 + curItemMT * 40 - 5, XMT[4], 425 + (curItemMT + 1) * 40 - 5);

				setbkcolor(BG_HOME_COLOR);
				settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 2);
				setcolor(TEXT_TITLE);
				DrawItemMT(curItemMT);

				DrawBorderDSMT();
			}

			// Ve item hien tai
			curItemMT = GetItemMTPosition(my);
			if (curItemMT != -1) {
				setfillstyle(SOLID_FILL, LINE);
				//				bar(XMT[0], 600 + curItemMT*40 - 8, XMT[4], 600+(curItemMT+1)*40-8);
				bar(XMT[0], 425 + curItemMT * 40 - 5, XMT[4], 425 + (curItemMT + 1) * 40 - 5);

				setbkcolor(LINE);
				settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 2);
				setcolor(BG_EDITTEXT_COLOR);

				DrawItemMT(curItemMT);

				DrawBorderDSMT();
			}
		}
	}
	else {
		if (curItemMT != -1) {
			// khoi phuc item
			setfillstyle(SOLID_FILL, BG_HOME_COLOR);
			//			bar(XMT[0], 600 + curItemMT*40 - 8, XMT[4], 600+(curItemMT+1)*40-8);
			bar(XMT[0], 425 + curItemMT * 40 - 5, XMT[4], 425 + (curItemMT + 1) * 40 - 5);

			setbkcolor(BG_HOME_COLOR);
			settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 2);
			setcolor(TEXT_TITLE);
			DrawItemMT(curItemMT);

			DrawBorderDSMT();
			curItemMT = -1;
		}
	}
}

void DrawItemMT(int i) {
	//settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 2);
	//setcolor(TEXT_TITLE);

//	outtextxy(XMT[0]+10, 600+i*40, DSMT.mt[i].MASACH);
//	outtextxy(XMT[1]+10, 600+i*40, DSMT.mt[i].TenSach);
//	outtextxy(XMT[2]+10, 600+i*40, DSMT.mt[i].NgayMuon);
//	outtextxy(XMT[3]+10, 600+i*40, TTMuonTra[DSMT.mt[i].TrangThai]);

	outtextxy(XMT[0] + 10, 425 + i * 40, DSMT.mt[i].MASACH);
	outtextxy(XMT[1] + 10, 425 + i * 40, DSMT.mt[i].TenSach);
	outtextxy(XMT[2] + 10, 425 + i * 40, DSMT.mt[i].NgayMuon);
	outtextxy(XMT[3] + 10, 425 + i * 40, TTMuonTra[DSMT.mt[i].TrangThai]);
}

void DrawItemMTQuaHan(int i) {
	settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 2);
	setcolor(TEXT_TITLE);

	//	outtextxy(XMT[0]+10, 600+i*40, DSMT.mt[i].MASACH);
	//	outtextxy(XMT[1]+10, 600+i*40, DSMT.mt[i].TenSach);
	//	outtextxy(XMT[2]+10, 600+i*40, DSMT.mt[i].NgayMuon);
	//	outtextxy(XMT[3]+10, 600+i*40, TTMuonTra[DSMT.mt[i].TrangThai]);

	outtextxy(XMT[0] + 10, 425 + i * 40 + 190, DSMT.mt[i].MASACH);
	outtextxy(XMT[1] + 10, 425 + i * 40 + 190, DSMT.mt[i].TenSach);
	outtextxy(XMT[2] + 10, 425 + i * 40 + 190, DSMT.mt[i].NgayMuon);
	outtextxy(XMT[3] + 10, 425 + i * 40 + 190, TTMuonTra[DSMT.mt[i].TrangThai]);
}

void DrawThongTinDocGia() {
	setfillstyle(SOLID_FILL, BG_HOME_COLOR);
	//bar(255, 200, 250+(w-250)/2-5, h);
	//ClearLayoutRightMuonTra();
	//bar(740, 180, w-15, 795);
	bar(60+w/2, 172, w - 15, 795);
	
	settextstyle(BOLD_FONT, HORIZ_DIR, 2);
	if (curDGMT == NULL) {
		setcolor(TIPS);
		bar(10, 170, 40 + w / 2, 795); //clear left screen
		bar(60+w/2, 150, w - 15, 795); //clear right screen 
		outtextxy(210, 200, "Khong tim thay doc gia nay");
	} 
	else {
		char ch[30];
		setfillstyle(SOLID_FILL, BG_HOME_COLOR);
		bar(10, 170, 40 + w / 2, 795);   //clear left screen
		settextstyle(BOLD_FONT, HORIZ_DIR, 2);
		setcolor(TEXT_COLOR);
		//outtextxy(300, 200, "Doc gia :");
		outtextxy(30, 170, "Doc gia :");
		sprintf(ch, "%s %s", curDGMT->ho, curDGMT->ten);
		//outtextxy(600, 200, ch);
		outtextxy(250, 170, ch);

		outtextxy(30, 220, "Ma the :");
		sprintf(ch, "%d", curDGMT->MATHE);
		outtextxy(250, 220, ch);

		outtextxy(30, 270, "Phai :");
		outtextxy(250, 270, PhaiDocGia[curDGMT->phai]);

		outtextxy(30, 320, "Trang thai the :");
		outtextxy(250, 320, TTTDocGia[curDGMT->trangthai]);

		settextstyle(BOLD_FONT, HORIZ_DIR, 3);
		setcolor(TEXT_TITLE_COLOR);
		outtextxy((XMT[0] + XMT[4]) / 2 - 50 - textwidth(DSDM) / 2, 360, DSDM);
		outtextxy((XMT[0] + XMT[4]) / 2 - 50 - textwidth(DSDM) / 2, 550, DSDMQH);

		DrawBorderDSMT();

		DrawBorderDSMTQuaHan();

		DSMT.n = 0;
		DauSach* ds;
		char chNow[15];
		strcpy(chNow, GetSystemDate());
		bool isQH = false;

		if (curDGMT->mt.chuaTra > 0) {
			DSMT.n = curDGMT->mt.chuaTra;
			int i = DSMT.n - 1;
			//for(NodeMuonTra *mt = curDGMT->mt.Last; mt != NULL; mt = mt->prev){
			for (NodeMuonTra* mt = curDGMT->mt.First; mt != NULL; mt = mt->next) {
				if (mt->muontra.trangthai != 1) {
					ds = GetDauSach(DSDS, mt->muontra.MASACH);
					strcpy(DSMT.mt[i].MASACH, mt->muontra.MASACH);
					strcpy(DSMT.mt[i].TenSach, ds->tensach);
					strcpy(DSMT.mt[i].NgayMuon, mt->muontra.ngaymuon);
					DSMT.mt[i].TrangThai = mt->muontra.trangthai;
					setbkcolor(BG_HOME_COLOR);
					settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 2);
					setcolor(TEXT_TITLE);
					DrawItemMT(i--);
				}
				if (mt->muontra.trangthai == 0) { 
					if (DiffTime(chNow, mt->muontra.ngaymuon) > 7 * 24 * 60 * 60) {
						i += 1;
						isQH = true;
						ds = GetDauSach(DSDS, mt->muontra.MASACH);
						strcpy(DSMT.mt[i].MASACH, mt->muontra.MASACH);
						strcpy(DSMT.mt[i].TenSach, ds->tensach);
						strcpy(DSMT.mt[i].NgayMuon, mt->muontra.ngaymuon);
						DSMT.mt[i].TrangThai = mt->muontra.trangthai;

						DrawItemMTQuaHan(i--);
					}
					else {
						i += 1;
						settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 2);
						setcolor(TEXT_TITLE);

						outtextxy(XMT[0] + 10, 425 + i * 40 + 190, "-----------");
						outtextxy(XMT[1] + 10, 425 + i * 40 + 190, "----------------------------------------");
						outtextxy(XMT[2] + 10, 425 + i * 40 + 190, "--------------");
						outtextxy(XMT[3] + 10, 425 + i * 40 + 190, "-------------------");
						i -= 1;
					}
				}
			}

		}

		if (curMenuMuonTra == btnMuonSach.id) {
			setcolor(TIPS);
			settextstyle(BOLD_FONT, HORIZ_DIR, 2);

			if (curDGMT->trangthai == 0) {
				// the bi khoa
				//outtextxy(1200, 250, "THE DOC GIA DANG BI KHOA, KHONG THE MUON SACH");
				settextstyle(BOLD_FONT, HORIZ_DIR, 5);
				outtextxy(70 + w / 2, 150, "THONG BAO NGHIEM TRONG!");
				settextstyle(BOLD_FONT, HORIZ_DIR, 2);
				outtextxy(70 + w / 2, 250, "THE DOC GIA DANG BI KHOA, KHONG THE MUON SACH");
				outtextxy(70 + w / 2, 300, "VUI LONG DEN SACH DE DUOC MO KHOA VA MUON SACH MOI");
				return;
			}
			if (DSMT.n >= 3) {
				//				outtextxy(1200, 250, "SO LUONG SACH MUON DA DAT GIOI HAN !");
				//				outtextxy(1200, 300, "VUI LONG TRA SACH TRUOC KHI MUON SACH MOI");
				settextstyle(BOLD_FONT, HORIZ_DIR, 5);
				outtextxy(70 + w / 2, 150, "THONG BAO NGHIEM TRONG!");
				settextstyle(BOLD_FONT, HORIZ_DIR, 2);
				outtextxy(70 + w / 2, 250, "SO LUONG SACH MUON DA DAT GIOI HAN !");
				outtextxy(70 + w / 2, 300, "VUI LONG TRA SACH TRUOC KHI MUON SACH MOI!");
				return;
			}
			if (isQH) {
				//				outtextxy(1200, 250, "DOC GIA DA MUON SACH QUA 7 NGAY ");
				//				outtextxy(1200, 300, "VUI LONG TRA SACH TRUOC KHI MUON SACH MOI");

				settextstyle(BOLD_FONT, HORIZ_DIR, 5);
				outtextxy(70 + w / 2, 150, "THONG BAO NGHIEM TRONG!");
				settextstyle(BOLD_FONT, HORIZ_DIR, 2);
				outtextxy(70 + w / 2, 250, "DOC GIA DA MUON SACH QUA 7 NGAY ");
				outtextxy(70 + w / 2, 300, "VUI LONG TRA SACH TRUOC KHI MUON SACH MOI");
				return;
			}

			edNhapMaSachMuonSach.draw();
			btnTimMaSach.draw();
			
			setcolor(BORDER_COLOR);
        	outtextxy(70 + w / 2, 80,"Nhap ma sach: "); 

		}
		else if (curMenuMuonTra == btnTraSach.id) {

		}


	}
}

void DrawThongTinSachTra(int itemMT) {
	if (itemMT != -1) {
		curMT = itemMT;


		setfillstyle(SOLID_FILL, BG_HOME_COLOR);
		//bar(250+(w-250)/2+5, 110, w, h); 
		bar(60+w/2, 180, w - 15, 795);

		settextstyle(BOLD_FONT, HORIZ_DIR, 5);
		setcolor(TEXT_TITLE_COLOR);
		outtextxy(900, 180, "THONG TIN SACH");

		settextstyle(BOLD_FONT, HORIZ_DIR, 2);
		setcolor(TEXT_COLOR);

		outtextxy(70 + w / 2, 240, "Ma sach :");
		outtextxy(230 + w / 2, 240, DSMT.mt[curMT].MASACH);

		outtextxy(70 + w / 2, 290, "Ten sach : ");
		outtextxy(230 + w / 2, 290, DSMT.mt[curMT].TenSach);

		outtextxy(70 + w / 2, 340, "Ngay muon :");
		outtextxy(230 + w / 2, 340, DSMT.mt[curMT].NgayMuon);

		setfillstyle(SOLID_FILL, BG_HOME_COLOR);
		//	bar(1100, 400, w-15,795); 
			//bar(740, 180, w-15,795); 

		if (subWindow == XAC_NHAN_TRA_SACH) {
			//			strcpy(edNhapNgayTraSach.content, GetSystemDate());
			edNhapNgayTraSach.draw();
			btnXacNhanTraSach.draw();
			btnLamMatSach.draw();

			settextstyle(BOLD_FONT, HORIZ_DIR, 2);
			setcolor(TIPS);
			//outtextxy(285+(w-250)/2 + 30 , 550, mess);
			outtextxy(70 + w / 2, 550, mess);

		}
		else if (subWindow == XAC_NHAN_LAM_MAT_SACH) {
			DrawLamMatSach();
		}
	}
}

void DrawLamMatSach() {
	setbkcolor(BG_HOME_COLOR);
	bar(60+w/2, 380, w - 15, 795);

	setcolor(TEXT_TITLE_COLOR);
	settextstyle(BOLD_FONT, HORIZ_DIR, 4);

	outtextxy(70 + w/2, 450, "LAM MAT SACH ?");
	setcolor(TIPS);
	settextstyle(BOLD_FONT, HORIZ_DIR, 2);
	//	outtextxy(1200, 550, "The doc gia se bi khoa");
	//	outtextxy(1200, 600, "Sach se chuyen qua trang thai: DA THANH LY");
	//	outtextxy(1200, 650, "Doc gia phai den sach moi co the tiep tuc muon sach");
	//	outtextxy(1200, 700, "Xac nhan lam mat sach ??");
	outtextxy(70 + w / 2, 500, "The doc gia se bi khoa");
	outtextxy(70 + w / 2, 550, "Sach se chuyen qua trang thai: DA THANH LY");
	outtextxy(70 + w / 2, 600, "Phai den sach moi co the tiep tuc muon sach");
	outtextxy(70 + w / 2, 650, "Xac nhan lam mat sach ??");

	btnXacNhanLamMatSach.draw();
	btnHuyLamMatSach.draw();
}

void DrawThongTinSach() {
	setfillstyle(SOLID_FILL, BG_HOME_COLOR);
	//bar(250+(w-250)/2+5, 200, w, h);
	bar(65 + w / 2, 160, w - 15, 795);
	settextstyle(BOLD_FONT, HORIZ_DIR, 2);
	setcolor(TEXT_COLOR);

	if (curSachMT != NULL) {
		

		outtextxy(70 + w / 2, 170, "Ma sach :");
		outtextxy(230 + w / 2, 170, curSachMT->MASACH);

		outtextxy(70 + w / 2, 220, "Ten sach : ");
		outtextxy(230 + w / 2, 220, curDSMT->tensach);

		outtextxy(70 + w / 2, 270, "Trang thai :");
		outtextxy(230 + w / 2, 270, TrangThaiSach[curSachMT->trangthai]);

		outtextxy(70 + w / 2, 320, "Vi tri :");
		outtextxy(230 + w / 2, 320, curSachMT->vitri);

		DSMT.n = 0;
		DauSach* ds;
		char chNow[15];
		strcpy(chNow, GetSystemDate());
		bool isQH = false;

		if (curSachMT->trangthai == 0) {
			for (NodeMuonTra* mt = curDGMT->mt.First; mt != NULL; mt = mt->next) {
				if (mt->muontra.trangthai != 1) {
					ds = GetDauSach(DSDS, mt->muontra.MASACH);
					if (ds->tensach == curDSMT->tensach) {
						setcolor(TIPS);
						outtextxy(70 + w / 2, 480, "DOC GIA KHONG THE MUON NHIEU HON 1 CUON SACH ");
						outtextxy(70 + w / 2, 520, "THUOC CUNG MOT DAU SACH ");
						outtextxy(70 + w / 2, 580, "=> DOC GIA KHONG THE MUON CUON SACH NAY !");
						return;
					}
				}
			}

			setcolor(TIPS);
			outtextxy(70 + w / 2, 480, "=> DOC GIA CO THE MUON CUON SACH NAY !");
			canMT = true;	// Co the muon sach
		}
		else if (curSachMT->trangthai == 1) {

			for (NodeMuonTra* mt = curDGMT->mt.First; mt != NULL; mt = mt->next) {
				if (mt->muontra.trangthai != 1) {
					ds = GetDauSach(DSDS, mt->muontra.MASACH);
					if (ds->tensach == curDSMT->tensach) {
						setcolor(TIPS);
						outtextxy(70 + w / 2, 480, "DOC GIA KHONG THE MUON NHIEU HON 1	CUON SACH ");
						outtextxy(70 + w / 2, 520, "THUOC CUNG MOT DAU SACH ");
						outtextxy(70 + w / 2, 580, "=> DOC GIA KHONG THE MUON CUON SACH NAY !");
						return;
					}
				}
			}

			setcolor(TIPS);
			outtextxy(70 + w / 2, 480, "=> DA CO NGUOI MUON CUON SACH NAY !");
			return;
		}
		else {
			setcolor(TIPS);
			outtextxy(70 + w / 2, 480, "=> SACH DA THANH LY, KHONG THE MUON !");
			return;
		}

		//		strcpy(edNhapNgayMuonSach.content, GetSystemDate());
		edNhapNgayMuonSach.draw();
		btnXacNhanMuonSach.draw();

		//cho nay khong co tac dung thi phai :) 
		setfillstyle(SOLID_FILL, BG_HOME_COLOR);
		//	bar(500, 740, w-15, 795); 
		setcolor(TIPS);
		settextstyle(BOLD_FONT, HORIZ_DIR, 2);
		outtextxy(70 + w / 2, 610, mess);
		//outtextxy(250+(w-1000)/2 + 30, 750, "NGUYENQUANGNIEN");

//		outtextxy(1200 + textwidth(ThongBao) + 40, 750, mess);
	}
	else {
		setcolor(TIPS);
		outtextxy(80 + w / 2, 250, "Khong tim thay sach nay!");
	}
}

void SetMenuButtonSwitch(int menuID) {
	btnMuonSach.isChoose = false;
	btnTraSach.isChoose = false;
	btnTopTen.isChoose = false;
	//btnCacSachQuaHan.isChoose = false;

	if (menuID == btnMuonSach.id) {
		btnMuonSach.isChoose = true;
	}
	else if (menuID == btnTraSach.id) {
		btnTraSach.isChoose = true;
	}
	else if (menuID == btnTopTen.id) {
		btnTopTen.isChoose = true;
	}
	//	else if(menuID == btnCacSachQuaHan.id){
	//		btnCacSachQuaHan.isChoose = true;
	//	}
}

void SetMenuMuonTraSelect(int menuID) {
	if (curMenuMuonTra != menuID) {
		curMenuMuonTra = menuID;
		curDGMT = NULL;
		curDSMT = NULL;
		Edit = NULL;
		strcpy(mess, "");
		ClearLayoutMainMuonTra();
		SetMenuButtonSwitch(curMenuMuonTra);

		if (curMenuMuonTra == btnMuonSach.id) {
			DrawMuonSach();
		}
		else if (curMenuMuonTra == btnTraSach.id) {
			DrawTraSach();
		}
		else if (curMenuMuonTra == btnTopTen.id) {
			DrawTopTen();
		}
		//		else if(curMenuMuonTra == btnCacSachQuaHan.id){
		//			DrawCacSachQuaHan();
		//		}

	}
}

void ClearLayoutLeftMuonTra() {
	setfillstyle(SOLID_FILL, BG_HOME_COLOR);
	//bar(255, 105, 250+(w-250)/2-5, h);
	bar(10, 50, 45 + w / 2, 795);
}

void ClearLayoutRightMuonTra() {
	setfillstyle(SOLID_FILL, BG_HOME_COLOR);
	//bar(250+(w-250)/2+5, 105, w, h);
	bar(55 + w / 2, 50, w - 15, 795);
}

void ClearLayoutMainMuonTra() {
	// xoa title
	setfillstyle(SOLID_FILL, BG_HOME_COLOR);
	//bar(255, 0, w, 95);
	//bar(0, 40, w, 95);
	// xoa content
	ClearLayoutLeftMuonTra();
	ClearLayoutRightMuonTra();
}

void DrawBorderMuonTra() {
	setfillstyle(SOLID_FILL, BG_HOME_COLOR);
	
	setlinestyle(SOLID_LINE, 0, 10);
	setcolor(15);
	rectangle(5, 45, w - 6, 800);
	line(50 + w / 2, 45, 50 + w / 2, h);


	rectangle(0, 0, 10, 40);
	rectangle(150, 0, 160, 40);
	rectangle(((w - 180) / 3 + 160), 0, ((w - 180) / 3 + 170), 40);
	rectangle(((w - 180) / 3) + 170 + (w - 180) / 3, 0, ((w - 180) / 3) + 180 + (w - 180) / 3, 40);
//	rectangle(-10 + (w - 180) / 3, 0, -10 + (w - 180) / 3 + 10 , 40);
	rectangle(w-10, 0, w, 40);
	//rectangle( -10+ (w-180)/4 + ((w-180)/4) +180 + (w-180)/4 ,0, (w-180)/4 + ((w-180)/4) +180 + (w-180)/4, 40);
}

void DrawMuonSach() {
	DrawBorderMuonTra();
	//line((w+150)/2, 100, 150+(w-150)/2, h);
	//line(100+ (w+150)/2, 60,100+ (w+150)/2, h);

	settextstyle(BOLD_FONT, HORIZ_DIR, 4);
	setcolor(TEXT_TITLE_COLOR);
	//outtextxy((w+150)/2 - textwidth(MuonSach)/2, 15, MuonSach);

	memset(edNhapMaDGMuonSach.content, 0, sizeof(edNhapMaDGMuonSach.content));
	edNhapMaDGMuonSach.draw();
	btnTimMaDG.draw();
	
	setcolor(BORDER_COLOR);
	outtextxy(30, 80,"Nhap ma the DG: "); 

}

void DrawTraSach() {
	DrawBorderMuonTra();
	//line((w+250)/2, 100, 250+(w-250)/2, h);
	//line((w+150)/2, 100, 150+(w-150)/2, h);
	//line(100+ (w+150)/2, 60,100+ (w+150)/2, h);

	settextstyle(BOLD_FONT, HORIZ_DIR, 4);
	setcolor(TEXT_TITLE_COLOR);
	//outtextxy((w+250)/2 - textwidth(MuonSach)/2, 15, TraSach);

	//khong biet thang duoi nay de lam j ?
	memset(edNhapMaDGMuonSach.content, 0, sizeof(edNhapMaDGMuonSach.content));
	edNhapMaDGMuonSach.draw();
	btnTimMaDG.draw();
	
	setcolor(BORDER_COLOR);
	outtextxy(30, 80,"Nhap ma the DG: "); 
}

void DrawTopTen() {
	DrawBorderMuonTra();

	settextstyle(BOLD_FONT, HORIZ_DIR, 4);
	setcolor(TEXT_TITLE_COLOR);
	//outtextxy((w+250)/2 - textwidth(TopTen)/2, 15, TopTen);

	setfillstyle(SOLID_FILL, BG_HOME_COLOR);
	bar(20, 50, w - 20, 795);

	settextstyle(BOLD_FONT, HORIZ_DIR, 2);

	char t[][20] = { "STT", "ISBN", "Ten sach", "So trang", "Tac gia", "NXB", "The loai", "So luot muon" };

	setlinestyle(SOLID_LINE, 0, 3);
	setcolor(TEXT_TITLE);
	//rectangle(XTT[0], 200, XTT[8], 880);
	rectangle(XTT[0], 100, XTT[8], 600);
	//line(XTT[0], 280, XTT[8], 280);
	line(XTT[0], 180, XTT[8], 180);
	for (int i = 0; i < 8; i++) {
		//line(XTT[i], 200, XTT[i], 880);
		setcolor(TEXT_TITLE);
		line(XTT[i], 100, XTT[i], 600);
		setcolor(BORDER_COLOR);
		//outtextxy((XTT[i+1]+XTT[i])/2 - textwidth(t[i])/2, 240-textheight(t[i])/2, t[i]);
		outtextxy((XTT[i + 1] + XTT[i]) / 2 - textwidth(t[i]) / 2, 140 - textheight(t[i]) / 2, t[i]);
	}

	TopSach topsach(DSDS); 
	//	DuyetDocGia(TreeDocGia, topsach);
	//	topsach.sort();
	char ch[20];
	setcolor(TEXT_TITLE);
	for (int i = 0; i < (topsach.n < 10 ? topsach.n : 10); i++) {
		itoa(i + 1, ch, 10); // chuyen i+1 vao mang ch , he co so la 10 

		outtextxy((XTT[0] + XTT[1]) / 2 - textwidth(ch) / 2, 200 + i * 40, ch);
		//cout<<"\n______________________topsach.list["<<i<<"].indexDS = "<<topsach.list[i].indexDS;
		outtextxy(XTT[1] + 10, 200 + i * 40, DSDS.nodes[topsach.list[i].indexDS]->ISBN);
		outtextxy(XTT[2] + 10, 200 + i * 40, DSDS.nodes[topsach.list[i].indexDS]->tensach);
		itoa(DSDS.nodes[topsach.list[i].indexDS]->sotrang, ch, 10);
		outtextxy(XTT[3] + 20, 200 + i * 40, ch);
		outtextxy(XTT[4] + 10, 200 + i * 40, DSDS.nodes[topsach.list[i].indexDS]->tacgia);
		itoa(DSDS.nodes[topsach.list[i].indexDS]->nxb, ch, 10);
		outtextxy((XTT[5] + XTT[6]) / 2 - textwidth(ch) / 2, 200 + i * 40, ch);
		outtextxy(XTT[6] + 10, 200 + i * 40, DSDS.nodes[topsach.list[i].indexDS]->theloai);
		itoa(topsach.list[i].cnt, ch, 10);
		outtextxy((XTT[7] + XTT[8]) / 2 - textwidth(ch) / 2, 200 + i * 40, ch);
	}
}


