#pragma once
#include"coreazs.h"
#include"coreviews.h" 
class VServClient :public WindowListener, public ViewListener, public LoadListener, public IFunctionJS {
public:

	VServClient();
	void SetWin(RefPtr<Window> win);
	void OnDOMReady(View* caller,
		uint64_t frame_id,
		bool is_main_frame,
		const String& url) override;
	virtual void OnClose() override;
	virtual void OnResize(uint32_t width, uint32_t height) override;
	virtual void OnChangeCursor(ultralight::View* caller,
		Cursor cursor);
	void LoadSite(std::string name,std::string argument);
	void SetTitle(std::string title) {
		this->title = title;
		win->SetTitle(title.c_str());
	}
	void AddSite(std::string url,std::string namefile,void(*LoadSite)(std::vector<string>*data)){
		site s;
		s.namefile=namefile;
		s.url=url;
		s.LoadSite=LoadSite;
		this->sites.push_back(s);
	}
	
	
	std::string GetArgument(){
		return argument;
	}
	// void SetAZS(AZS* azs){
	// 	this->azs=azs;
	// }
	// AZS* GetAZS(){
	// 	return azs;
	// }
	
	~VServClient();
	database_t db;
	db_table_t tb_tovar;
	tovar_node_t* tovars;
private:
	std::string argument;
	std::string title;
	RefPtr<Window> win;
	RefPtr<Overlay> ov;
	
};