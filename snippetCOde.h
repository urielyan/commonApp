
//Qt表格控件一些常用的设置封装，QTableWidget继承自QTableView，所以下面这个函数支持传入QTableWidget。
void QUIHelper::initTableView(QTableView *tableView, int rowHeight, bool headVisible, bool edit)
{
    //奇数偶数行颜色交替
    tableView->setAlternatingRowColors(false);
    //垂直表头是否可见
    tableView->verticalHeader()->setVisible(headVisible);
    //选中一行表头是否加粗
    tableView->horizontalHeader()->setHighlightSections(false);
    //最后一行拉伸填充
    tableView->horizontalHeader()->setStretchLastSection(true);
    //行标题最小宽度尺寸
    tableView->horizontalHeader()->setMinimumSectionSize(0);
    //行标题最大高度
    tableView->horizontalHeader()->setMaximumHeight(rowHeight);
    //默认行高
    tableView->verticalHeader()->setDefaultSectionSize(rowHeight);
    //选中时一行整体选中
    tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    //只允许选择单个
    tableView->setSelectionMode(QAbstractItemView::SingleSelection);

    //表头不可单击
#if (QT_VERSION > QT_VERSION_CHECK(5,0,0))
    tableView->horizontalHeader()->setSectionsClickable(false);
#else
    tableView->horizontalHeader()->setClickable(false);
#endif

    //鼠标按下即进入编辑模式
    if (edit) {
        tableView->setEditTriggers(QAbstractItemView::CurrentChanged | QAbstractItemView::DoubleClicked);
    } else {
        tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    }
}

//用QFile.readAll()读取QSS文件默认是ANSI格式，不支持UTF8，如果在QtCreator中打开qss文件来编辑保存，这样很可能导致qss加载以后没有效果。
void initStyle()
{
    //加载样式表
    QString qss;
    //QFile file(":/qss/psblack.css");
    //QFile file(":/qss/flatwhite.css");
    QFile file(":/qss/lightblue.css");
    if (file.open(QFile::ReadOnly)) {
#if 1
        //用QTextStream读取样式文件不用区分文件编码 带bom也行
        QStringList list;
        QTextStream in(&file);
        //in.setCodec("utf-8");
        while (!in.atEnd()) {
            QString line;
            in >> line;
            list << line;
        }

        qss = list.join("\n");
#else
        //用readAll读取默认支持的是ANSI格式,如果不小心用creator打开编辑过了很可能打不开
        qss = QLatin1String(file.readAll());
#endif
        QString paletteColor = qss.mid(20, 7);
        qApp->setPalette(QPalette(QColor(paletteColor)));
        qApp->setStyleSheet(qss);
        file.close();
    }
}

//很多时候需要在已知背景色的情况下，能够清晰的绘制文字，这个时候需要计算对应的文字颜色。
//根据背景色自动计算合适的前景色
double gray = (0.299 * color.red() + 0.587 * color.green() + 0.114 * color.blue()) / 255;
QColor textColor = gray > 0.5 ? Qt::black : Qt::white;


//在使用setItemWidget或者setCellWidget的过程中，有时候会发现设置的控件没有居中显示而是默认的左对齐，而且不会自动拉伸填充，对于追求完美的程序员来说，
//这个可不大好看，有个终极通用办法就是，将这个控件放到一个widget的布局中，然后将widget添加到item中，这样就完美解决了，而且这样可以组合多个控件产生复
杂的控件。

//实例化进度条控件
QProgressBar *progress = new QProgressBar;
//增加widget+布局巧妙实现居中
QWidget *widget = new QWidget;
QHBoxLayout *layout = new QHBoxLayout;
layout->setSpacing(0);
layout->setMargin(0);
layout->addWidget(progress);
widget->setLayout(layout);
ui->tableWidget->setCellWidget(0, 0, widget);

//在很多网络应用程序，需要自定义心跳包来保持连接，不然断电或者非法关闭程序，对方识别不到，需要进行超时检测，但是有些程序没有提供心跳协议，
//此时需要启用系统层的保活程序，此方法适用于TCP连接。

int fd = tcpSocket->socketDescriptor();
int keepAlive = 1;      //开启keepalive属性,缺省值:0(关闭)
int keepIdle = 5;       //如果在5秒内没有任何数据交互,则进行探测,缺省值:7200(s)
int keepInterval = 2;   //探测时发探测包的时间间隔为2秒,缺省值:75(s)
int keepCount = 2;      //探测重试的次数,全部超时则认定连接失效,缺省值:9(次)
setsockopt(fd, SOL_SOCKET, SO_KEEPALIVE, (void *)&keepAlive, sizeof(keepAlive));
setsockopt(fd, SOL_TCP, TCP_KEEPIDLE, (void *)&keepIdle, sizeof(keepIdle));
setsockopt(fd, SOL_TCP, TCP_KEEPINTVL, (void *)&keepInterval, sizeof(keepInterval));
setsockopt(fd, SOL_TCP, TCP_KEEPCNT, (void *)&keepCount, sizeof(keepCount));

//Qt中继承QWidget之后，样式表不起作用，解决办法有三个。强烈推荐方法一。

//方法一：设置属性 this->setAttribute(Qt::WA_StyledBackground, true);
///方法二：改成继承QFrame，因为QFrame自带paintEvent函数已做了实现，在使用样式表时会进行解析和绘制。
//方法三：重新实现QWidget的paintEvent函数时，使用QStylePainter绘制。
void Widget::paintEvent(QPaintEvent *)
{
    QStyleOption option;
    option.initFrom(this);
    QPainter painter(this);
    style()->drawPrimitive(QStyle::PE_Widget, &option, &painter, this);
}


#if 0
判断编译器类型、编译器版本、操作系统。

//GCC编译器
#ifdef __GNUC__
#if __GNUC__ >= 3 // GCC3.0以上

//MSVC编译器
#ifdef _MSC_VER
#if _MSC_VER >=1000 // VC++4.0以上
#if _MSC_VER >=1100 // VC++5.0以上
#if _MSC_VER >=1200 // VC++6.0以上
#if _MSC_VER >=1300 // VC2003以上
#if _MSC_VER >=1400 // VC2005以上
#if _MSC_VER >=1500 // VC2008以上
#if _MSC_VER >=1600 // VC2010以上
#if _MSC_VER >=1700 // VC2012以上
#if _MSC_VER >=1800 // VC2013以上
#if _MSC_VER >=1900 // VC2015以上

//Borland C++
#ifdef __BORLANDC__

//Cygwin
#ifdef __CYGWIN__
#ifdef __CYGWIN32__

//mingw
#ifdef __MINGW32__

//windows
#ifdef _WIN32    //32bit
#ifdef _WIN64    //64bit
#ifdef _WINDOWS     //图形界面程序
#ifdef _CONSOLE     //控制台程序
//Windows（95/98/Me/NT/2000/XP/Vista）和Windows CE都定义了
#if (WINVER >= 0x030a)     // Windows 3.1以上
#if (WINVER >= 0x0400)     // Windows 95/NT4.0以上
#if (WINVER >= 0x0410)     // Windows 98以上
#if (WINVER >= 0x0500)     // Windows Me/2000以上
#if (WINVER >= 0x0501)     // Windows XP以上
#if (WINVER >= 0x0600)     // Windows Vista以上
//_WIN32_WINNT 内核版本
#if (_WIN32_WINNT >= 0x0500) // Windows 2000以上
#if (_WIN32_WINNT >= 0x0501) // Windows XP以上
#if (_WIN32_WINNT >= 0x0600) // Windows Vista以上

#endif
