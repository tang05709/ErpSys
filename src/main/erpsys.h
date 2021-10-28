#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QLabel>
#include <QTreeView>
#include <QVBoxLayout>
#include <QStandardItemModel>
#include <QPushButton>

class ErpSys : public QWidget
{
    Q_OBJECT

public:
    ErpSys(QWidget *parent = nullptr);
    ~ErpSys();

    QLabel *curPath; // 访问路径
    QVBoxLayout *contentLayout; // 局部切换区域
    void deleteContentLayoutWidget(); // 局部切换时释放子布局
    void initWindow();
    void initMain();
    void initFooter();
    void loadStyle();
    void setErpTitle(const QString title);

public slots:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void winExit();
    void winSizeMax();
    void winSizeMin();
    void winLogout();

private slots:
    void treeViewChanged(QModelIndex index);
    void homeClick();
    void updateCurTime();

private:
    // 左侧
    QLabel *company; // 系统名称
    QTreeView *menus; // 树形菜单

    // 右侧
    QPushButton *home;// 返回主页按钮
    QLabel *welcome; // 主页欢迎语

    // 底部
    QLabel *copyright; // 底部备案信息
    QLabel *curTime; // 底部显示时间

    QStandardItemModel mainTreeModel;
    QPoint erpPos;

};
#endif // WIDGET_H
