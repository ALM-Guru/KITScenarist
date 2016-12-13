#include "CrashReportDialog.h"
#include "ui_CrashReportDialog.h"

using UserInterface::CrashReportDialog;


CrashReportDialog::CrashReportDialog(QWidget* _parent) :
	QLightBoxDialog(_parent),
	m_ui(new Ui::CrashReportDialog)
{
	m_ui->setupUi(this);
}

CrashReportDialog::~CrashReportDialog()
{
	delete m_ui;
}

QWidget* CrashReportDialog::focusedOnExec() const
{
	return m_ui->email;
}

void CrashReportDialog::initView()
{
	m_ui->buttons->addButton(tr("Send report"), QDialogButtonBox::AcceptRole);
	m_ui->buttons->addButton(tr("Don't send"), QDialogButtonBox::RejectRole);

	QLightBoxDialog::initView();
}

void CrashReportDialog::initConnections()
{
	connect(m_ui->buttons, &QDialogButtonBox::accepted, this, &CrashReportDialog::accept);
	connect(m_ui->buttons, &QDialogButtonBox::rejected, this, &CrashReportDialog::reject);

	QLightBoxDialog::initConnections();
}
