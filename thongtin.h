
void RunThongTin(){
//	btnQuayVe.draw();
	
	settextstyle(BOLD_FONT, HORIZ_DIR, 7);
	setcolor(TEXT_TITLE_COLOR);
	setbkcolor(11);
	outtextxy(100, 50, "MENU");
	
	setcolor(8);
	rectangle(5,5,400,h-100); //khung trai
	rectangle(10,10,395,h-105); //khung trai con 
   	rectangle(405,5,w-10,h-100); //khung cha phai
    rectangle(410,10,w-15,160); //khung con phai tren
    rectangle(410,170,w-15,h-105); //khung con phai duoi
	
	settextstyle(BOLD_FONT, HORIZ_DIR, 7);
	setcolor(TEXT_TITLE_COLOR);
	setbkcolor(11);
	outtextxy(200+w/2-textwidth(AppTitle)/2, 50, AppTitle);
	
	 
	btnQLDauSach.draw();
	btnQLDocGia.draw();
	btnQLSach.draw();
	btnThongTin.draw();
	btnThoat.draw();
	
	// ve giao dien
	setcolor(0);	// chon mau chu
	settextstyle(BOLD_FONT, HORIZ_DIR, 3);		// chon font chu, huong ve chu (direction), size chu
	
	char *uni = "Hoc vien Cong nghe Buu Chinh Vien Thong - TPHCM";
	char *khoa =   "* Khoa       :";
	char *khoa2 = "2019 - 2024";
	char *title =  "* Mon hoc    :";
	char *title2 = "Cau Truc Du Lieu & Giai Thuat";
	char *gv =     "* Giang vien :";
	char *gv2 = "Luu Nguyen Ky Thu";
	char *doan =   "* Do An      :";
	char *doan2 = "Quan Ly Thu Vien";
	char *sv =     "* Sinh vien  :";
	char *author1 = "1. Nguyen Quang Nien - N19DCCN116 - D19CQCN01-N";
	char *author2 = "2. Vu Thi Hong Oanh  - N19DCCN135 - D19CQCN01-N";
	
	settextstyle(BOLD_FONT, HORIZ_DIR, 4);
	outtextxy(435, 200, uni);
	
	settextstyle(BOLD_FONT, HORIZ_DIR, 2);
	outtextxy(500, 300, title);
	outtextxy(500, 360, gv);
	outtextxy(500, 420, doan);
	outtextxy(500, 480, sv);
	outtextxy(500, 600, khoa);
	
	outtextxy(700, 300, title2);
	outtextxy(700, 360, gv2);
	outtextxy(700, 420, doan2);
	
	outtextxy(700, 480, author1);
	outtextxy(700, 540, author2);
	
	outtextxy(700, 600, khoa2);
}

void ThongTinEvent(){
	//ButtonEffect(btnQuayVe);
	ButtonEffect(btnQLDauSach);
	ButtonEffect(btnQLDocGia);
	ButtonEffect(btnQLSach);
	ButtonEffect(btnThongTin);
	ButtonEffect(btnThoat);	
	
	if(GetAsyncKeyState(VK_LBUTTON)){
//		if(btnQuayVe.isMouseHover(mx, my)){
//			SetMenuSelect(0);
//		}
		if(btnQLDauSach.isMouseHover(mx, my)){
			SetMenuSelect(btnQLDauSach.id);
		}
		else if(btnQLDocGia.isMouseHover(mx, my)){
			SetMenuSelect(btnQLDocGia.id);
		}
		else if(btnQLSach.isMouseHover(mx, my)){
			SetMenuSelect(btnQLSach.id);
		}
		else if(btnThoat.isMouseHover(mx, my)){
			isExit = true;
		}
	}
}
