//#include "NXI.h"
#include "NXInterface.h"



int NXinterface::nx_test() {

    const char   dst_ptrfile[] = "D:\\env_tr\\u\\trptr\\tanhuangguan-shiyanmoxing.prt";

    // ��ʼ��
    NXOpen::Session* session = NXOpen::Session::GetSession();

    // ����ģ��
    NXOpen::BasePart* base_part;
    NXOpen::PartLoadStatus* status;

    try {       //��*.prt�ļ�
        base_part = session->Parts()->OpenBaseDisplay(dst_ptrfile, &status);
    }
    catch (NXOpen::NXException& e) {
        std::cout << e.Message() << std::endl;
        std::cout << "Open model successfully.\n";
        return -1;
    }



    NXOpen::Part* work_part = session->Parts()->Work();
    delete status;
    std::cout << "Open model successfully." << std::endl;

    //NXOpen::Expression* expression(dynamic_cast<NXOpen::Expression*>(work_part->Expressions()->FindObject("H1")));
    //work_part->Expressions()->Edit(expression, "2");

    NXOpen::Expression* expression(dynamic_cast<NXOpen::Expression*>(work_part->Expressions()->FindObject("p2'10")));
    work_part->Expressions()->Edit(expression, "3.922");

    for (auto p = work_part->Expressions()->begin(); p != work_part->Expressions()->end(); p++) {
        std::cout << (*p)->Name().GetText() << ", ";
        std::cout << (*p)->Equation().GetLocaleText() << ", ";
        std::cout << (*p)->Type().GetLocaleText() << std::endl;
    }
    std::cout << "Updated model successfully." << std::endl;

    //����
    NXOpen::PartSaveStatus* save_status;
    save_status = work_part->Save(NXOpen::BasePart::SaveComponentsTrue, NXOpen::BasePart::CloseAfterSaveFalse);

    //��鱣��״̬
    if (int unsaved = save_status->NumberUnsavedParts()) {
        std::cout << unsaved << " part(s) cannot be saved." << std::endl;
    }
    std::cout << "All parts saved successfully." << std::endl;
    delete save_status;


    return 0;

}


int NXinterface::UgRun(const ParamSet& param_set, int times, QString save_file_name, QString& error_message)
{
	if (times > (int)(param_set.InputParamsCount() / param_set.GetInputParamSize()))
	{
		qDebug() << "number of runs is over range.";
		return -1;
	}

	try {//��*.prt�ļ�
		// ��ʼ��
		NXOpen::Session* session = NXOpen::Session::GetSession();
		//�ر�ԭ��Parts
		auto* parts = session->Parts();
		NXOpen::PartCloseResponses* response{ nullptr };
		parts->CloseAll(NXOpen::BasePart::CloseModifiedUseResponses, response);
		// ����ģ��
		NXOpen::PartLoadStatus* status{ nullptr };
		auto file_name = param_set.GetModelName();
		qDebug()  << file_name;
		NXOpen::BasePart* base_part = parts->OpenBaseDisplay(file_name.toLocal8Bit().constData(), &status);
		NXOpen::Part* work_part = parts->Work();

		//TODO �ж�status	
		//qInfo() << "Open model successfully.";
		delete status;

		//���²���
		QString error_msg;
		bool is_success = true;

		int param_size = (int)param_set.GetInputParamSize();
		int param_index = times * param_size;



		for (size_t i = param_index; i < (param_index + param_size); i++)
		{
			QString param_name = param_set.GetInputParam(i, PARAM_NAME);
			QString param_value = param_set.GetInputParam(i, PARAM_VALUE);
			//NXOpen::Expression* expression{ nullptr };
			//auto name_tmp = param_name.toLocal8Bit().constData();
			std::string name = param_name.toUtf8().constData();//
			std::string value = param_value.toUtf8().constData();

			try {
				NXOpen::Expression* expression = work_part->Expressions()->FindObject(name.c_str());
				//work_part->Expressions()->Edit(expression, value.c_str());
				expression->SetRightHandSide(value.c_str());
			}
			catch (NXOpen::NXException& e) {
				qDebug() << e.what();
				error_msg += QString(u8"���²���ʧ�ܣ�����ֵ�Ƿ�����Ч��Χ�ڣ���������") + QString(name.c_str());
				is_success = false;
			}

			if (!is_success) {
				qInfo() << error_msg;
				error_message = error_msg;


				return -1;
			}

			for (size_t i = param_index; i < (param_index + param_size); i++)
			{
				QString param_name = param_set.GetInputParam(i, PARAM_NAME);
				QString param_value = param_set.GetInputParam(i, PARAM_VALUE);
				//NXOpen::Expression* expression{ nullptr };
				//auto name_tmp = param_name.toLocal8Bit().constData();
				std::string name = param_name.toUtf8().constData();//
				std::string value = param_value.toUtf8().constData();

				//name = "p62'10";				/* ģ��ParamSet */
				//value = "-0.5";			/* ģ��ParamSet */

				NXOpen::Expression* expression = work_part->Expressions()->FindObject(name.c_str());



				//qInfo() << expression->Equation().GetLocaleText() << " " << expression->Type().GetLocaleText() <<" ";


				if (expression->Units() == nullptr) {
					qInfo() << expression->Equation().GetLocaleText() << " "
						<< expression->Type().GetLocaleText() << " "
						<< "No Units \n";
				}
				else {
					qInfo() << expression->Equation().GetLocaleText() << " "
						<< expression->Type().GetLocaleText() << " "
						<< expression->Units()->Name().getLocaleText() << "\n";
				}


				/*qInfo() << expression->Equation().GetLocaleText() << " " << expression->Type().GetLocaleText()
					<< " " << expression->Units()->Name().getLocaleText();*/
			}
			qInfo() << "Updated model successfully.";


			NXOpen::PartSaveStatus* save_status;
			save_status = work_part->Save(NXOpen::BasePart::SaveComponentsTrue, NXOpen::BasePart::CloseAfterSaveFalse);
			if (int unsaved = save_status->NumberUnsavedParts()) {
				qWarning() << unsaved << " part(s) cannot be saved.";
				// 			auto tp = save_status->GetPart(unsaved-1);
				// 			QString fp = tp->FullPath().GetText();
				// 			qWarning() << fp;


			}
			else {
				qInfo() << "All parts saved successfully.";
			}
			delete save_status;


			QFile temp_ug_file(save_file_name);
			if (temp_ug_file.exists()) {
				temp_ug_file.remove();
			}
			std::string tmp = save_file_name.toUtf8().constData();

			work_part->SaveAs(tmp.c_str());
			qInfo() << "prt file saved successfully.";

		}
	}
	catch (NXOpen::NXException& e)
	{
		
		qWarning() << e.what();
		error_message = e.what();
		return -1;
	}
	return 0;

}

//��ȡȫ�����ʽ�����ӹ���
QStringList NXinterface::GetExpression(QString file_name) {
	QStringList Expression_list;
	try {
		NXOpen::Session* session = NXOpen::Session::GetSession();//��ȡ����
		auto* parts = session->Parts();
		NXOpen::PartCloseResponses* response{ nullptr };
		parts->CloseAll(NXOpen::BasePart::CloseModifiedUseResponses, response);//�ر��Ѵ򿪵Ĳ���

		NXOpen::PartLoadStatus* status{ nullptr };
		NXOpen::BasePart* base_part = parts->OpenBaseDisplay(file_name.toLocal8Bit().constData(), &status);//�򿪲���
		NXOpen::Part* work_part = parts->Work();

		delete status;
		NXOpen::ExpressionCollection* expressionCollection = work_part->Expressions();
		for (auto it = expressionCollection->begin(); it != expressionCollection->end(); it++) {
			NXOpen::Expression* expression = dynamic_cast<NXOpen::Expression*>(*it);
			QString tmp = expression->Name().GetLocaleText();
			Expression_list.append(tmp);

		}

	}
	catch(NXOpen::NXException& e){ 
		qWarning() << e.what();
		return Expression_list;
	}


	return Expression_list;
}

int NXinterface::GetUgUnitType(const ParamSet& param_set, QString& error_message)
{
	try
	{
		NXOpen::Session* session = NXOpen::Session::GetSession();//��ȡ����
		auto* parts = session->Parts();
		NXOpen::PartCloseResponses* response{ nullptr };
		parts->CloseAll(NXOpen::BasePart::CloseModifiedUseResponses, response);//�ر��Ѵ򿪵Ĳ���
		// ����ģ��
		NXOpen::PartLoadStatus* status{ nullptr };
		auto file_name = param_set.GetModelName();
		NXOpen::BasePart* base_part = parts->OpenBaseDisplay(file_name.toLocal8Bit().constData(), &status);//�򿪲���

		qInfo() << file_name;

		NXOpen::Part* work_part = parts->Work();
		delete status;
		//��ȡ����  
		int parmsize = (int)param_set.GetInputParamSize();
		//���²���
		QString error_msg;
		bool is_success = true;
		int all_param_size = param_set.InputParamsCount();
		//int param_size = (int)param_set.GetInputParamSize();
		//int param_index = times * param_size;


		for (size_t i = 0; i < all_param_size; ++i)
		{
			QString param_name = param_set.GetInputParam(i, PARAM_NAME);
			QString param_value = param_set.GetInputParam(i, PARAM_VALUE);
			std::string name = param_name.toUtf8().constData();
			std::string value = param_value.toUtf8().constData();
			//�������
			try {
				NXOpen::Expression* expression = work_part->Expressions()->FindObject(name.c_str());  //�쳣����������ڲ���ģ�Ͳ������Ĳ���
				const_cast<ParamSet&> (param_set).SetInputParam(i, 2, QString(expression->Units()->Name().getLocaleText()));
				const_cast<ParamSet&>(param_set).SetInputParam(i, 3, QString(expression->Type().GetLocaleText()));
			}
			catch (NXOpen::NXException& e) {
				qDebug() << param_name << e.what();
				if (QString(name.c_str()) == "nan") {
					continue;
				}
				if (error_msg.contains(QString(name.c_str()))) {
					continue;
				}
				error_msg += QString(u8"�������ô���,��������") + QString(name.c_str());
				is_success = false;
			}
		}

		if (!is_success)
		{
			qInfo() << error_msg;
			error_message = error_msg;
			return -1;
		}
	}
	catch (NXOpen::NXException& e)
	{
		qWarning() << e.what();
		return -1;
	}
	return 0;
}

QStringList NXinterface::SelectUgParams(const QString& file_name)
{
	QStringList param_list;
	try
	{
		NXOpen::Session* session = NXOpen::Session::GetSession();//��ȡ����
		auto* parts = session->Parts();
		NXOpen::PartCloseResponses* response{ nullptr };
		parts->CloseAll(NXOpen::BasePart::CloseModifiedUseResponses, response);//�ر��Ѵ򿪵Ĳ���
		// ����ģ��
		NXOpen::PartLoadStatus* status{ nullptr };
		NXOpen::BasePart* base_part = parts->OpenBaseDisplay(file_name.toLocal8Bit().constData(), &status);//�򿪲���

		NXOpen::Part* work_part = parts->Work();
		//�ر�
		delete status;

		NXOpen::ExpressionCollection* expressionCollection = work_part->Expressions();

		for (auto it = expressionCollection->begin(); it != expressionCollection->end(); ++it)
		{
			NXOpen::Expression* expression = dynamic_cast<NXOpen::Expression*>(*it);
			QString tmp = expression->Name().GetLocaleText();
			//����p��ͷ+���һλ������
			QRegularExpression regex("^p\\d");
			QRegularExpressionMatch filter = regex.match(tmp);
			//qInfo() << tmp;
			if (filter.hasMatch()) {
				//param_list.append(tmp);
				continue;
			}
			else {
				param_list.append(tmp);
			}
		}
	}
	catch (NXOpen::NXException& e)
	{

		qWarning() << e.what();
		return param_list;
	}
	return param_list;
}



