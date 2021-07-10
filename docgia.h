void RunDocGia() {
	strcpy(mess, "");

	ClearContentThemDocGia();

	DrawDanhSachDocGia();

	btnSapXepTen.isChoose = sortDGByName;
	btnSapXepMaThe.isChoose = !btnSapXepTen.isChoose;

	btnSapXepTen.isHover = sortDGByName;
	btnSapXepMaThe.isHover = !sortDGByName;

	btnSapXepTen.draw();
	btnSapXepMaThe.draw();

	btnTatCaDocGia.isHover = true;
	btnTatCaDocGia.isChoose = true;
	btnDocGiaQuaHan.isChoose = false;
	btnDocGiaQuaHan.isHover = false;

	btnTatCaDocGia.draw();
	btnDocGiaQuaHan.draw();

	DSDG.GetAllDocGia(TreeDocGia);

	DrawListDocGia(true);
	Window = THEM_DOC_GIA;
	if (btnTatCaDocGia.isChoose) DrawThemDocGia();

	//setlinestyle(SOLID_LINE, 0, 10);
	setcolor(8);     
	setlinestyle(SOLID_LINE, 0, 1);
	//rectangle(810 + 110, 5, w - 7, 550);
    //rectangle(810 + 105, 5, w - 5, 755);
    rectangle(810 + 110, 5, w - 10, 765);
    rectangle(810 + 115, 10, w - 15, 550);

    //rectangle(2, 5, 810 + 105, 755);
    rectangle(2, 5, 810 + 105, 765);
}

void DocGiaEvent() {

	ButtonEffect(btnQuayVe);
	ButtonEffect(btnTatCaDocGia);
	ButtonEffect(btnDocGiaQuaHan);

	if (Window == THEM_DOC_GIA) {
		ButtonEffect(btnThemDocGia);
	}
	else if (Window == HIEU_CHINH_DOC_GIA) {
		ButtonEffect(btnHieuChinhDocGia);
		//ButtonEffect(btnBackToThemDocGia); //ko dung backto , thay vao do dung huy
		ButtonEffect(btnHuyXoaDocGia);
	}
	else if (Window == XOA_DOC_GIA) {
		if (curDG != -1) {
			//ButtonEffect(btnHuyXoaDocGia); 
			ButtonEffect(btnXacNhanXoaDocGia);
		}
		ButtonEffect(btnHuyXoaDocGia);
		//ButtonEffect(btnBackToThemDocGia);
	}
	else if (Window == HIEU_CHINH_DOC_GIA_DONE) {
		ButtonEffect(btnHuyXoaDocGia);
	}

	ItemDocGiaEvent();

	if (btnTatCaDocGia.isChoose) {
		ButtonEffect(btnPrevDocGia);
		ButtonEffect(btnNextDocGia);

		ButtonEffect(btnFirstDocGia);
		ButtonEffect(btnLastDocGia);

		ButtonEffect(btnSapXepTen);
		ButtonEffect(btnSapXepMaThe);
	}
	else {
		ButtonEffect(btnPrevDocGiaQH);
		ButtonEffect(btnNextDocGiaQH);

		ButtonEffect(btnFirstDocGiaQH);
		ButtonEffect(btnLastDocGiaQH);
	}

	if (GetAsyncKeyState(VK_LBUTTON)) {
		if (btnQuayVe.isMouseHover(mx, my)) {
			SetMenuSelect(0);
		}
		// Switch
		ButtonSwitchClick();
		ItemDGLeftMouseClick();

		if (Window == THEM_DOC_GIA) {
			if (btnThemDocGia.isMouseHover(mx, my)) {
				if (CheckThemDocGia()) {
					DocGia docgia(edThemMaTheDocGia.toInt(),
						edThemHoDocGia.trim(),
						edThemTenDocGia.trim(),
						edThemPhaiDocGia.toInt(),
						edThemTrangThaiTheDocGia.toInt());

					InsertDocGia(TreeDocGia, docgia);
					insertAfter_ID(nodeStart, edThemMaTheDocGia.toInt());

					//					if(btnTatCaDocGia.isChoose){
					//		                ButtonEffect(btnPrevDocGia);
					//			 		 	ButtonEffect(btnNextDocGia);
					//			 		 	ButtonEffect(btnSapXepTen);
					//			 		 	ButtonEffect(btnSapXepMaThe);
					//		 		 	}else{
					//			 		 	ButtonEffect(btnPrevDocGiaQH);
					//			 		 	ButtonEffect(btnNextDocGiaQH);
					//		 		 	}

					strcpy(mess, "Them doc gia thanh cong!");
					ClearContentThemDocGia();
					ClearLayoutListDocGia();
					DrawListDocGia(true);
					DrawThemDocGia();
				}
				else {
					DrawThemDocGia(false);
				}

			}

			if (edThemHoDocGia.isMouseHover(mx, my)) {
				Edit = &edThemHoDocGia;
			}
			else if (edThemTenDocGia.isMouseHover(mx, my)) {
				Edit = &edThemTenDocGia;
			}
			else if (edThemPhaiDocGia.isMouseHover(mx, my)) {
				Edit = &edThemPhaiDocGia;
			}
			else if (edThemTrangThaiTheDocGia.isMouseHover(mx, my)) {
				Edit = &edThemTrangThaiTheDocGia;
			}

		}
		else if (Window == HIEU_CHINH_DOC_GIA) {
			if (btnHieuChinhDocGia.isMouseHover(mx, my)) {
				if (curDG != -1 && CheckHieuChinhDocGia()) {
					DocGia docgia(edHieuChinhMaTheDocGia.toInt(),
						edHieuChinhHoDocGia.trim(),
						edHieuChinhTenDocGia.trim(),
						edHieuChinhPhaiDocGia.toInt(),
						edHieuChinhTrangThaiTheDocGia.toInt());
					UpdateDocGia(TreeDocGia, docgia);

					Window = HIEU_CHINH_DOC_GIA_DONE;

					strcpy(mess, "Hieu chinh doc gia thanh cong!");
					//ClearContentHieuChinhDocGia();

					ClearLayoutListDocGia();
					DrawListDocGia(true);
					curDG = -1;
				}
				DrawHieuChinhDocGia();
				DrawHieuChinhDocGiaDone();
			}
			else if (btnHuyXoaDocGia.isMouseHover(mx, my)) { // because huyxodocgia equivalent huyhieuchinhdocgia
				Window = THEM_DOC_GIA;
				ClearRightLayoutDocGia();
				strcpy(mess, "");
				DrawThemDocGia();
			}

			if (curDG != -1) {
				if (edHieuChinhHoDocGia.isMouseHover(mx, my)) {
					Edit = &edHieuChinhHoDocGia;
				}
				else if (edHieuChinhTenDocGia.isMouseHover(mx, my)) {
					Edit = &edHieuChinhTenDocGia;
				}
				else if (edHieuChinhPhaiDocGia.isMouseHover(mx, my)) {
					Edit = &edHieuChinhPhaiDocGia;
				}
				else if (edHieuChinhTrangThaiTheDocGia.isMouseHover(mx, my)) {
					Edit = &edHieuChinhTrangThaiTheDocGia;
				}
			}

		}
		else if (Window == XOA_DOC_GIA) {
			if (btnXacNhanXoaDocGia.isMouseHover(mx, my) && curDG != -1) {
				// neu doc gia k muon sach nao thi co the xoa
				if (DSDG.nodes[curDG]->mt.total == 0) {
					delete_ID(DSDG.nodes[curDG]->MATHE);
					RemoveDocGia(TreeDocGia, DSDG.nodes[curDG]->MATHE);

					strcpy(mess, "Xoa doc gia thanh cong!");
					curDG = -1;
					ClearLayoutListDocGia();
					DrawListDocGia(true);
					ClearRightLayoutDocGia();
					DrawXoaDocGia(curDG);
					btnHuyXoaDocGia.draw();
				}
				else {
					// Doc gia dang muon sach -> k the xoa
					strcpy(mess, "Doc gia da muon sach nen khong the xoa!");
					DrawXoaDocGia(curDG);
				}

			}
			else if (btnHuyXoaDocGia.isMouseHover(mx, my)) {
				Window = THEM_DOC_GIA;
				ClearRightLayoutDocGia();
				strcpy(mess, "");
				DrawThemDocGia();
			}
		}
		else if (Window == HIEU_CHINH_DOC_GIA_DONE) {
			if (btnHuyXoaDocGia.isMouseHover(mx, my)) {
				Window = THEM_DOC_GIA;
				ClearRightLayoutDocGia();
				strcpy(mess, "");
				DrawThemDocGia();
			}
		}

		if (btnBackToThemDocGia.isMouseHover(mx, my) && Window != THEM_DOC_GIA) {
			strcpy(mess, "");
			Window = THEM_DOC_GIA;
			ClearRightLayoutDocGia();
			DrawThemDocGia();
		}

		if (btnTatCaDocGia.isChoose) {
			// Tat ca Doc gia - MODE

			if (btnPrevDocGia.isMouseHover(mx, my)) {
				if (curPageDG > 1) {
					curPageDG--;
					ClearLayoutListDocGia();
					DrawListDocGia();
				}
			}
			else if (btnNextDocGia.isMouseHover(mx, my)) {
				if (curPageDG < totalPageDG) {
					curPageDG++;
					ClearLayoutListDocGia();
					DrawListDocGia();
				}
			}
			else if (btnFirstDocGia.isMouseHover(mx, my)) {
				if (curPageDG > 1) {
				curPageDG = 1;
				ClearLayoutListDocGia();
				DrawListDocGia();
				}
			}
			else if (btnLastDocGia.isMouseHover(mx, my)) {
				if (curPageDG < totalPageDG) {
				curPageDG = totalPageDG;
				ClearLayoutListDocGia();
				DrawListDocGia();
				}
			}

		}
		else {
			// Doc Gia Qua Han - MODE
			if (btnPrevDocGiaQH.isMouseHover(mx, my)) {
				if (curPageDGQuaHan > 1) {
					curPageDGQuaHan--;
					ClearLayoutListDocGiaQuaHan();
					DrawListDocGia();
				}
			}
			else if (btnNextDocGiaQH.isMouseHover(mx, my)) {
				if (curPageDGQuaHan < totalPageDGQuaHan) {
					curPageDGQuaHan++;
					ClearLayoutListDocGiaQuaHan();
					DrawListDocGia();
				}
			}
			else if (btnFirstDocGiaQH.isMouseHover(mx, my)) {
				if (curPageDGQuaHan > 1) {
					curPageDGQuaHan = 1;
					ClearLayoutListDocGiaQuaHan();
					DrawListDocGia();
				}
			}
			else if (btnLastDocGiaQH.isMouseHover(mx, my)) {
				if (curPageDGQuaHan < totalPageDGQuaHan) {
					curPageDGQuaHan = totalPageDGQuaHan;
					ClearLayoutListDocGiaQuaHan();
					DrawListDocGia();
				}
			}
		}

	}
	else if (GetAsyncKeyState(VK_RBUTTON)) {
		ItemDGRightMouseClick();
	}
}

void ButtonSwitchClick() {
	if (btnTatCaDocGia.isMouseHover(mx, my)) {
		if (!btnTatCaDocGia.isChoose) {
			btnDocGiaQuaHan.isChoose = false;
			btnTatCaDocGia.isChoose = true;
			curItemDG = -1;
			// Get list docgia
//			DSDG.GetAllDocGia(TreeDocGia);


			ClearLayoutListDocGiaQuaHan();
			DrawListDocGia(true);
			//Window = THEM_DOC_GIA;  //niendztest luc dau la dong , thu mo ra xem sao
			//DrawThemDocGia();		//niendztest luc dau la dong , thu mo ra xem sao
			DrawDanhSachDocGia();

			btnSapXepTen.isChoose = sortDGByName;
			btnSapXepMaThe.isChoose = !btnSapXepTen.isChoose;

			btnSapXepTen.isHover = sortDGByName;
			btnSapXepMaThe.isHover = !sortDGByName;

			btnSapXepTen.draw();
			btnSapXepMaThe.draw();
		}
	}
	else if (btnDocGiaQuaHan.isMouseHover(mx, my)) {
		if (!btnDocGiaQuaHan.isChoose) {
			btnTatCaDocGia.isChoose = false;
			btnDocGiaQuaHan.isChoose = true;
			curItemDG = -1;
			// Get list docgia qua han
			DSDG.GetDocGiaQuaHan(TreeDocGia);

			//setfillstyle(SOLID_FILL, BG_COLOR);
			setfillstyle(SOLID_FILL, BG_HOME_COLOR);
			bar(4, 70, 500, 500);
			ClearLayoutListDocGiaQuaHan();
			DrawListDocGia();
		}
	}

	if (btnSapXepTen.isMouseHover(mx, my)) {
		if (!sortDGByName) {
			sortDGByName = true;
			ClearLayoutListDocGia();
			DrawListDocGia();
		}
	}
	else if (btnSapXepMaThe.isMouseHover(mx, my)) {
		if (sortDGByName) {
			sortDGByName = false;
			ClearLayoutListDocGia();
			DrawListDocGia();
		}
	}
	btnSapXepTen.isChoose = sortDGByName;
	btnSapXepMaThe.isChoose = !sortDGByName;

}

void ItemDocGiaEvent() {
	if (mx > XDG[0] && mx < XDG[btnTatCaDocGia.isChoose ? 5 : 6] && my > 160 - 8 && my < 160 + 10 * 30 - 8) {

		if (curItemDG != GetItemDocGiaPosition(my)) {
			if (curItemDG != -1) {
				// khoi phuc item
				//setfillstyle(SOLID_FILL, BG_COLOR);
				setfillstyle(SOLID_FILL, BG_HOME_COLOR);

				bar(XDG[0], 160 + curItemDG * 30 - 8, XDG[btnTatCaDocGia.isChoose ? 5 : 6], 160 + (curItemDG + 1) * 30);

				//setbkcolor(BG_COLOR);
				setbkcolor(BG_HOME_COLOR);
				settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 2);
				setcolor(TEXT_TITLE);

				if (btnTatCaDocGia.isChoose) {
					DrawItemDocGia(*DSDG.nodes[(curPageDG - 1) * 10 + curItemDG], (curPageDG - 1) * 10 + curItemDG);
					DrawBorderDSDocGia();
				}
				else {
					DrawItemDocGiaQuaHan(*DSDG.nodes[(curPageDGQuaHan - 1) * 10 + curItemDG], DSDG.soNgayQH[(curPageDGQuaHan - 1) * 10 + curItemDG], (curPageDGQuaHan - 1) * 10 + curItemDG);
					DrawBorderDSDocGiaQuaHan();
				}
			}

			// Ve item hien tai
			curItemDG = GetItemDocGiaPosition(my);
			if (curItemDG != -1) {
				setfillstyle(SOLID_FILL, LINE);

				bar(XDG[0], 160 + curItemDG * 30 - 8, XDG[btnTatCaDocGia.isChoose ? 5 : 6], 160 + (curItemDG + 1) * 30);

				settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 2);
				setbkcolor(LINE);
				setcolor(BG_EDITTEXT_COLOR);

				if (btnTatCaDocGia.isChoose) {
					//setbkcolor(LINE);
					DrawItemDocGia(*DSDG.nodes[(curPageDG - 1) * 10 + curItemDG], (curPageDG - 1) * 10 + curItemDG);
					DrawBorderDSDocGia();
				}
				else {
					//setbkcolor(LINE);
					DrawItemDocGiaQuaHan(*DSDG.nodes[(curPageDGQuaHan - 1) * 10 + curItemDG], DSDG.soNgayQH[(curPageDGQuaHan - 1) * 10 + curItemDG], (curPageDGQuaHan - 1) * 10 + curItemDG);
					DrawBorderDSDocGiaQuaHan();
				}
			}
		}
	}
	else {
		if (curItemDG != -1) {
			// khoi phuc item
			//setfillstyle(SOLID_FILL, BG_COLOR);
			setfillstyle(SOLID_FILL, BG_HOME_COLOR);
			bar(XDG[0], 160 + curItemDG * 30 - 8, XDG[btnTatCaDocGia.isChoose ? 5 : 6], 160 + (curItemDG + 1) * 30);
			//setbkcolor(BG_COLOR);
			setbkcolor(BG_HOME_COLOR);
			settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 2);
			//setcolor(TEXT_COLOR);
			setcolor(TEXT_TITLE);

			if (btnTatCaDocGia.isChoose) {
				DrawItemDocGia(*DSDG.nodes[(curPageDG - 1) * 10 + curItemDG], (curPageDG - 1) * 10 + curItemDG);
				DrawBorderDSDocGia();
			}
			else {
				DrawItemDocGiaQuaHan(*DSDG.nodes[(curPageDGQuaHan - 1) * 10 + curItemDG], DSDG.soNgayQH[(curPageDGQuaHan - 1) * 10 + curItemDG], (curPageDGQuaHan - 1) * 10 + curItemDG);
				DrawBorderDSDocGiaQuaHan();
			}

			curItemDG = -1;
		}
	}
}

//tao ma tu dong
void AutoGenMaDocGia() {
	nodeStart = Node_ID_Random();
	if (nodeStart != NULL) {
		int ranID ;
		ranID = rand() % (nodeStart->next->id - nodeStart->id - 1) + nodeStart->id + 1;
		itoa(ranID, edThemMaTheDocGia.content, 10);
	}
	else {
		strcpy(edThemMaTheDocGia.content, "OVERFLOW");
	}
}

bool CheckThemDocGia() {
	if (strcmp(edThemMaTheDocGia.content, "OVERFLOW") == 0) {
		strcpy(mess, "So luong doc gia dat gioi han");
		return false;
	}

	if (strlen(edThemHoDocGia.content) == 0) {
		strcpy(mess, "Ho va ten dem khong duoc bo trong");
		Edit = &edThemHoDocGia;
		Edit->draw();
		return false;
	}
	else if (strlen(edThemTenDocGia.content) == 0) {
		strcpy(mess, "Ten khong duoc bo trong");
		Edit = &edThemTenDocGia;
		Edit->draw();
		return false;
	}
	else if (strlen(edThemPhaiDocGia.content) == 0) {
		strcpy(mess, "Phai khong duoc bo trong");
		Edit = &edThemPhaiDocGia;
		Edit->draw();
		return false;
	}
	else if (strlen(edThemTrangThaiTheDocGia.content) == 0) {
		strcpy(mess, "Trang thai the khong duoc bo trong");
		Edit = &edThemTrangThaiTheDocGia;
		Edit->draw();
		return false;
	}

	return true;
}

bool CheckHieuChinhDocGia() {
	if (strlen(edHieuChinhHoDocGia.content) == 0) {
		strcpy(mess, "Ho va ten dem khong duoc bo trong");
		Edit = &edHieuChinhHoDocGia;
		Edit->draw();
		return false;
	}
	else if (strlen(edHieuChinhTenDocGia.content) == 0) {
		strcpy(mess, "Ten khong duoc bo trong");
		Edit = &edHieuChinhTenDocGia;
		Edit->draw();
		return false;
	}
	else if (strlen(edHieuChinhPhaiDocGia.content) == 0) {
		strcpy(mess, "Phai khong duoc bo trong");
		Edit = &edHieuChinhPhaiDocGia;
		Edit->draw();
		return false;
	}
	else if (strlen(edHieuChinhTrangThaiTheDocGia.content) == 0) {
		strcpy(mess, "Trang thai the khong duoc bo trong");
		Edit = &edHieuChinhTrangThaiTheDocGia;
		Edit->draw();
		return false;
	}

	return true;
}

void ClearContentThemDocGia() {
	memset(edThemMaTheDocGia.content, 0, sizeof(edThemMaTheDocGia.content)); //set sizeof(edThemMaTheDocGia.content) byte begin from edThemMaTheDocGia.content to 0
	memset(edThemHoDocGia.content, 0, sizeof(edThemHoDocGia.content));
	memset(edThemTenDocGia.content, 0, sizeof(edThemTenDocGia.content));
	memset(edThemPhaiDocGia.content, 0, sizeof(edThemPhaiDocGia.content));
	memset(edThemTrangThaiTheDocGia.content, 0, sizeof(edThemTrangThaiTheDocGia.content));
}

void ClearContentHieuChinhDocGia() {
	memset(edHieuChinhMaTheDocGia.content, 0, sizeof(edHieuChinhMaTheDocGia.content));
	memset(edHieuChinhHoDocGia.content, 0, sizeof(edHieuChinhHoDocGia.content));
	memset(edHieuChinhTenDocGia.content, 0, sizeof(edHieuChinhTenDocGia.content));
	memset(edHieuChinhPhaiDocGia.content, 0, sizeof(edHieuChinhPhaiDocGia.content));
	memset(edHieuChinhTrangThaiTheDocGia.content, 0, sizeof(edHieuChinhTrangThaiTheDocGia.content));
}

void DrawDanhSachDocGia() {
	settextstyle(BOLD_FONT, HORIZ_DIR, 4);
	setcolor(TEXT_TITLE_COLOR);
	setbkcolor(11);
	outtextxy((XDG[0] + XDG[5]) / 2 - textwidth(DocGiaTitle) / 2, 15, DocGiaTitle);

	settextstyle(BOLD_FONT, HORIZ_DIR, 2);
	setcolor(TEXT_TITLE_COLOR);
	setbkcolor(11);
	outtextxy(10, 70, "Sap xep theo:");

	btnQuayVe.draw();
	btnTatCaDocGia.draw();
	btnDocGiaQuaHan.draw();
	btnPrevDocGia.draw();
	btnNextDocGia.draw();
	btnFirstDocGia.draw();
	btnLastDocGia.draw();
	btnSapXepTen.draw();
	btnSapXepMaThe.draw();
}

void ClearLayoutListDocGia() {
	setfillstyle(SOLID_FILL, BG_HOME_COLOR);
	//bar(XDG[0]-5, 150-5, XDG[5]+5, 820);
	//bar(XDG[0]-5, 80, XDG[5]+5, 550+ 50);
	//bar(XDG[0] - 1, 110 - 5, XDG[5] + 5, 800);
	bar(XDG[0] - 1, 110 - 5, XDG[5] + 5, 755);
}

void ClearLayoutListDocGiaQuaHan() {
	setfillstyle(SOLID_FILL, BG_HOME_COLOR);
	//bar(XDG[0]-5, 150-5, XDG[6]+5, 820);
	//bar(XDG[0]-5, 110-5, XDG[6]+5, 550 + 50);
//	bar(XDG[0] - 1, 109, XDG[6] + 5, 800);
    bar(XDG[0] - 1, 109, XDG[6] + 5, 755);
	bar(180, 55, 380, 105);
}

void DrawBorderDSDocGia() {
	setlinestyle(SOLID_LINE, 0, 3);
	setcolor(TEXT_TITLE);
	//rectangle(XDG[0], 150, XDG[5], 750);
	rectangle(XDG[0], 110, XDG[5], 460);
	//line(XDG[0], 150 + 25 + 2*20, XDG[5], 150 + 25 + 2*20);
	line(XDG[0], 125 + 10 + 2 * 10 - 3, XDG[5], 125 + 10 + 2 * 10 - 3);
	for (int i = 0; i < 5; i++) {
		line(XDG[i + 1], 110, XDG[i + 1], 460);
	}

	char ch[6][20] = { "Ma the", "Ho va ten dem", "Ten", "Phai", "TTT" };
	settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 1);
	for (int i = 0; i < 5; i++) {
		setcolor(BORDER_COLOR);
		setbkcolor(BG_HOME_COLOR);
		outtextxy(XDG[i] + (XDG[i + 1] - XDG[i]) / 2 - textwidth(ch[i]) / 2, 122, ch[i]);
	}
}

void DrawBorderDSDocGiaQuaHan() {
	setlinestyle(SOLID_LINE, 0, 3);
	setcolor(TEXT_TITLE);
	rectangle(XDG[0], 110, XDG[6], 460);
	//line(XDG[0], 150 + 25 + 2*20, XDG[6], 150 + 25 + 2*20);
	line(XDG[0], 125 + 10 + 2 * 10 - 3, XDG[6], 125 + 10 + 2 * 10 - 3);
	for (int i = 0; i < 6; i++) {
		line(XDG[i + 1], 110, XDG[i + 1], 460);
	}
	char ch[7][20] = { "Ma the", "Ho va ten dem", "Ten", "Phai", "TTT", "SNQH" };
	settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 1);
	setcolor(BORDER_COLOR);
	for (int i = 0; i < 6; i++) {
		setbkcolor(BG_HOME_COLOR);
		outtextxy(XDG[i] + (XDG[i + 1] - XDG[i]) / 2 - textwidth(ch[i]) / 2, 122, ch[i]);
	}
}

void DrawListDocGia(bool reload) {
	char chPage[20];

	if (reload && btnTatCaDocGia.isChoose) DSDG.GetAllDocGia(TreeDocGia);

	if (btnTatCaDocGia.isChoose) {

		DrawBorderDSDocGia();

		if (sortDGByName) {
			DSDG.SortTenDocGia();
		}
		else {
			DSDG.SortMaTheDocGia();
		}
		//paging
		totalPageDG = (DSDG.n - 1) / 10 + 1;
		setcolor(TEXT_TITLE);
		for (int i = 10 * (curPageDG - 1); i < 10 * curPageDG; i++) {
			if (i >= DSDG.n) break;
			DrawItemDocGia(*DSDG.nodes[i], i); 
		}

		// num page

		sprintf(chPage, "%d / %d", curPageDG, totalPageDG);
		settextstyle(BOLD_FONT, HORIZ_DIR, 2);
		//outtextxy((XDG[5]+XDG[0])/2 - textwidth(chPage)/2, 580, chPage);
		outtextxy(380, 495, chPage);

		btnPrevDocGia.draw();
		btnNextDocGia.draw();
		btnFirstDocGia.draw();
		btnLastDocGia.draw();

	}
	else if (btnDocGiaQuaHan.isChoose) {
		DrawBorderDSDocGiaQuaHan();
		//		DSDG.GetDocGiaQuaHan(TreeDocGia);
		
		totalPageDGQuaHan = (DSDG.n - 1) / 10 + 1;

		setbkcolor(BG_HOME_COLOR);
		setcolor(TEXT_TITLE);
		for (int i = 10 * (curPageDGQuaHan - 1); i < 10 * curPageDGQuaHan; i++) {
			if (i >= DSDG.n) break;
			DrawItemDocGiaQuaHan(*DSDG.nodes[i], DSDG.soNgayQH[i], i);
		}

		// num page
		sprintf(chPage, "%d / %d", curPageDGQuaHan, totalPageDGQuaHan);
		settextstyle(BOLD_FONT, HORIZ_DIR, 2);
		//outtextxy( (XDG[0]+XDG[6])/2 - textwidth(chPage)/2, 580, chPage);
		outtextxy(430, 495, chPage);


		btnPrevDocGiaQH.draw();
		btnNextDocGiaQH.draw();
		btnFirstDocGiaQH.draw();
		btnLastDocGiaQH.draw();
	}

	setcolor(TIPS);
	rectangle(5, 580, XDG[5], 750);
	outtextxy(20, 590, " ________________________Huong dan su dung________________________");
	outtextxy(20, 620, " * Click chuot trai : Hieu chinh doc gia");
	outtextxy(20, 650, " * Click chuot phai : Xoa doc gia");
	outtextxy(20, 680, " * TTT              : Trang thai the");
	outtextxy(20, 710, " * SNQH             : So ngay qua han");
	
	rectangle(925, 580, w-20, 730);
	outtextxy(940, 590, " ______________Huong dan su dung______________");
	outtextxy(940, 620, " * H & TD : Ho va ten dem");
	outtextxy(940, 650, " * TT[0,1]: Trang thai (0: khoa - 1: hoat dong)");
	outtextxy(940, 680, "");
	outtextxy(940, 710, "");
}

void DrawThemDocGia(bool genNewID) {
	settextstyle(BOLD_FONT, HORIZ_DIR, 4);
	setcolor(TEXT_TITLE_COLOR);
    
	outtextxy((XDG[6] + 20 + w - 15) / 2 - textwidth(ThemDauSach) / 2, 45, ThemDocGia);

	settextstyle(BOLD_FONT, HORIZ_DIR, 2);
	setcolor(TEXT_TITLE_COLOR);
	setbkcolor(BG_HOME_COLOR);
	//outtextxy(XDG[6]+20, 485-textheight(ThongBao)/2, ThongBao);
	
	setfillstyle(SOLID_FILL, BG_HOME_COLOR);
	bar(810 + 120, 485 - textheight(ThongBao) / 2, w-20, 510); 
	outtextxy(810 + 120, 485 - textheight(ThongBao) / 2, ThongBao);

	setfillstyle(SOLID_FILL, BG_HOME_COLOR);
	//outtextxy(XDG[6]+25 + textwidth(ThongBao), 485-textheight(ThongBao)/2, mess);
	outtextxy(810 + 125 + textwidth(ThongBao), 485 - textheight(ThongBao) / 2, mess);

	setbkcolor(BG_HOME_COLOR);

	if (genNewID) AutoGenMaDocGia();
	strcpy(edThemTrangThaiTheDocGia.content, "1");

	edThemMaTheDocGia.draw();
	edThemHoDocGia.draw();
	edThemTenDocGia.draw();
	edThemPhaiDocGia.draw();
	edThemTrangThaiTheDocGia.draw();

	btnThemDocGia.draw();
}

void GetHieuChinhDocGia(int i) {
	curDG = i;
	ClearContentHieuChinhDocGia();

	char ch[10];
	itoa(DSDG.nodes[i]->MATHE, ch, 10);
	strcpy(edHieuChinhMaTheDocGia.content, ch);
	strcpy(edHieuChinhHoDocGia.content, DSDG.nodes[i]->ho);
	strcpy(edHieuChinhTenDocGia.content, DSDG.nodes[i]->ten);
	itoa(DSDG.nodes[i]->phai, ch, 10);
	strcpy(edHieuChinhPhaiDocGia.content, ch);
	itoa(DSDG.nodes[i]->trangthai, ch, 10);
	strcpy(edHieuChinhTrangThaiTheDocGia.content, ch);
	// Clear
	ClearRightLayoutDocGia();
	DrawHieuChinhDocGia();
}

void DrawHieuChinhDocGia() {

	setbkcolor(BG_HOME_COLOR);
	settextstyle(BOLD_FONT, HORIZ_DIR, 4);
	setcolor(TEXT_TITLE_COLOR);
	outtextxy(40 + (XDG[6] + 20 + w - 15) / 2 - textwidth(HieuChinhDocGia) / 2, 45, HieuChinhDocGia);

	settextstyle(BOLD_FONT, HORIZ_DIR, 2);
	setcolor(TEXT_TITLE_COLOR);
	outtextxy(810 + 120, 485 - textheight(ThongBao) / 2, ThongBao);

	setfillstyle(SOLID_FILL, BG_HOME_COLOR);
	outtextxy(810 + 125 + textwidth(ThongBao), 485 - textheight(ThongBao) / 2, mess);

	edHieuChinhMaTheDocGia.draw();
	edHieuChinhHoDocGia.draw();
	edHieuChinhTenDocGia.draw();
	edHieuChinhPhaiDocGia.draw();
	edHieuChinhTrangThaiTheDocGia.draw();

	btnHieuChinhDocGia.draw();
	//btnBackToThemDocGia.draw();
	btnHuyXoaDocGia.draw();
}

void DrawXoaDocGia(int i) {
	setbkcolor(BG_HOME_COLOR);
	settextstyle(BOLD_FONT, HORIZ_DIR, 4);
	setcolor(TEXT_TITLE_COLOR);
	//	rectangle
	(XDG[6]+20, 210, w-15, 700);
	//	line(XDG[6]+20, 280, w-15, 280);
	//	line(XDG[6]+20, 650, w-15, 650);
	//	outtextxy(40+  (XDG[6]+20+w-15)/2 - textwidth(XoaDocGia)/2, 245 - textheight(XoaDocGia)/2, XoaDocGia);
	outtextxy(30 + (XDG[6] + 20 + w - 15) / 2 - textwidth(XoaDocGia) / 2, 45, XoaDocGia);

	if (i != -1) {
		settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 2);
		setcolor(BG_ADD);
		curDG = i;

		char ch[50];
		sprintf(ch, "%s %s", DSDG.nodes[i]->ho, DSDG.nodes[i]->ten);
		setcolor(BORDER_COLOR);
		outtextxy(810 + 120, 120, "Doc gia :");
		setcolor(BG_ADD);
		outtextxy(810 + 360, 120, ch);

		setcolor(BORDER_COLOR);
		itoa(DSDG.nodes[i]->MATHE, ch, 10);
		outtextxy(810 + 120, 160, "Ma the :");
		setcolor(BG_ADD);
		outtextxy(810 + 360, 160, ch);

		setcolor(BORDER_COLOR);
		outtextxy(810 + 120, 200, "Phai :");
		setcolor(BG_ADD);
		outtextxy(810 + 360, 200, PhaiDocGia[DSDG.nodes[i]->phai]);

		setcolor(BORDER_COLOR);
		outtextxy(810 + 120, 240, "Trang thai the :");
		setcolor(BG_ADD);
		outtextxy(810 + 360, 240, TTTDocGia[DSDG.nodes[i]->trangthai]);

		setcolor(BORDER_COLOR);
		outtextxy(810 + 120, 280, "So sach dang muon :");
		setcolor(BG_ADD);
		itoa(DSDG.nodes[i]->mt.chuaTra, ch, 10);
		//		itoa(SoSachDangMuon(TreeDocGia, DSDG.nodes[i]->MATHE), ch, 10);
		outtextxy(810 + 360, 280, ch);

		setcolor(BORDER_COLOR);
		outtextxy(810 + 120, 320, "Tong so sach da muon :");
		setcolor(BG_ADD);
		itoa(DSDG.nodes[i]->mt.total, ch, 10);
		//		itoa(SoSachDaMuon(TreeDocGia, DSDG.nodes[i]->MATHE), ch, 10);
		outtextxy(810 + 360, 320, ch);


		btnXacNhanXoaDocGia.draw();
		btnHuyXoaDocGia.draw();
	}

	//	setcolor(TIPS);
	//	settextstyle(BOLD_FONT, HORIZ_DIR, 2);
	//	outtextxy(XDG[6]+50, 675-textheight(ThongBao)/2, ThongBao);
	//	setfillstyle(SOLID_FILL, BG_HOME_COLOR);
	//	bar(XDG[6]+50 + textwidth(ThongBao), 675-textheight(ThongBao)/2, w-20, 675+textheight(ThongBao)/2);
	//	outtextxy(XDG[6]+70 + textwidth(ThongBao), 675-textheight(ThongBao)/2, mess);

	settextstyle(BOLD_FONT, HORIZ_DIR, 2);
	setcolor(TEXT_TITLE_COLOR);
	outtextxy(810 + 120, 485 - textheight(ThongBao) / 2, ThongBao);

	setfillstyle(SOLID_FILL, BG_HOME_COLOR);
	//outtextxy(XDG[6]+18 + textwidth(ThongBao), 485-textheight(ThongBao)/2, mess);
	outtextxy(810 + 125, 30 + 485 - textheight(ThongBao) / 2, mess);

	//btnBackToThemDocGia.draw();
}

void DrawHieuChinhDocGiaDone() {
	btnHuyXoaDocGia.draw();
	setbkcolor(BG_HOME_COLOR);
	setfillstyle(SOLID_FILL, BG_HOME_COLOR);
	bar(810 + 170, 390, 810 + 170 + 150, 390 + 50);
}


void ItemDGLeftMouseClick() {
	if (curItemDG != -1) {
		strcpy(mess, "");
		Window = HIEU_CHINH_DOC_GIA;
		if (btnTatCaDocGia.isChoose)
			GetHieuChinhDocGia(10 * (curPageDG - 1) + curItemDG);
		else
			GetHieuChinhDocGia(10 * (curPageDGQuaHan - 1) + curItemDG);
	}
}

void ItemDGRightMouseClick() {
	if (curItemDG != -1) {
		strcpy(mess, "");
		Window = XOA_DOC_GIA;
		ClearRightLayoutDocGia();
		if (btnTatCaDocGia.isChoose)
			DrawXoaDocGia(10 * (curPageDG - 1) + curItemDG);
		else
			DrawXoaDocGia(10 * (curPageDGQuaHan - 1) + curItemDG);

	}
}

int GetItemDocGiaPosition(int y) {
	//	int pos = (y-220+8)/40;
	int pos = (y - 160 + 8) / 30;
	//cout<<"\n____________________________pos = "<<pos;
	int i;
	if (btnTatCaDocGia.isChoose) {
		i = 10 * (curPageDG - 1) + pos;
	//	cout<<"\n______________________ i = "<<i;
	}
	else {
		i = 10 * (curPageDGQuaHan - 1) + pos;
	//	cout<<"\n______________________ i = "<<i;
	}
	if (i >= DSDG.n) return -1;
	return pos;
}

void DrawItemDocGia(DocGia& docgia, int i) {
	//	setcolor(BG_COLOR);
	settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 1);
	//setbkcolor(BG_HOME_COLOR);
	i %= 10;
	char ch[6];
	itoa(docgia.MATHE, ch, 10);//chuyen docgia.MATHE -> string , he co so 10, luu vao trong ch
	//outtextxy(XDG[0] + 10, 220 + i*40, ch);
	outtextxy(XDG[0] + 5, 160 + i * 30, ch);
	outtextxy(XDG[1] + 5, 160 + i * 30, docgia.ho);
	outtextxy(XDG[2] + 5, 160 + i * 30, docgia.ten);
	outtextxy(XDG[3] + 5, 160 + i * 30, PhaiDocGia[docgia.phai]);
	if (TTTDocGia[docgia.trangthai] == "HOAT DONG") outtextxy(XDG[4] + 10, 160 + i * 30, "HD");
	else if (TTTDocGia[docgia.trangthai] == "KHOA") outtextxy(XDG[4] + 10, 160 + i * 30, "K");
}

void DrawItemDocGiaQuaHan(DocGia& docgia, int soNgayQH, int i) {
	//setbkcolor(BG_HOME_COLOR);
//	setcolor(BG_COLOR);
    i %= 10; //nien custom
	settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 1);
	DrawItemDocGia(docgia, i);
	char ch[4];
	sprintf(ch, "%d", soNgayQH);
	outtextxy(XDG[5] + 5, 160 + i * 30, ch);
}

void ClearRightLayoutDocGia() {
	setfillstyle(SOLID_FILL, BG_HOME_COLOR);
	bar(810 + 116, 20, w - 17, 530);
}

