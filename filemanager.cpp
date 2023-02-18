#include <QtWidgets>

class FileManager : public QWidget {
public:
    FileManager(QWidget *parent = nullptr) : QWidget(parent) {
        create_ui();
    }

private:
    void create_ui() {
        file_model_ = new QFileSystemModel(this);
        file_model_->setRootPath(QDir::rootPath());
        file_model_->setReadOnly(false);
        file_model_->setFilter(QDir::AllEntries | QDir::NoDotAndDotDot);

        file_view_ = new QTreeView(this);
        file_view_->setModel(file_model_);
        file_view_->setRootIndex(file_model_->index(QDir::rootPath()));
        file_view_->setSelectionMode(QAbstractItemView::ExtendedSelection);
        file_view_->setDragEnabled(true);
        file_view_->setAcceptDrops(true);
        file_view_->setDropIndicatorShown(true);

        file_view_->header()->setSectionResizeMode(QHeaderView::ResizeToContents);

        connect(file_view_, SIGNAL(doubleClicked(const QModelIndex&)), this, SLOT(open_file(const QModelIndex&)));

        file_menu_ = new QMenu(this);

        create_file_action_ = new QAction(tr("Create File"), this);
        connect(create_file_action_, SIGNAL(triggered()), this, SLOT(create_file()));

        create_folder_action_ = new QAction(tr("Create Folder"), this);
        connect(create_folder_action_, SIGNAL(triggered()), this, SLOT(create_folder()));

        rename_action_ = new QAction(tr("Rename"), this);
        connect(rename_action_, SIGNAL(triggered()), this, SLOT(rename()));

        move_action_ = new QAction(tr("Move"), this);
        connect(move_action_, SIGNAL(triggered()), this, SLOT(move()));

        copy_action_ = new QAction(tr("Copy"), this);
        connect(copy_action_, SIGNAL(triggered()), this, SLOT(copy()));

        delete_action_ = new QAction(tr("Delete"), this);
        connect(delete_action_, SIGNAL(triggered()), this, SLOT(delete_item()));

        file_menu_->addAction(create_file_action_);
        file_menu_->addAction(create_folder_action_);
        file_menu_->addSeparator();
        file_menu_->addAction(rename_action_);
        file_menu_->addAction(move_action_);
        file_menu_->addAction(copy_action_);
        file_menu_->addSeparator();
        file_menu_->addAction(delete_action_);

        file_view_->setContextMenuPolicy(Qt::CustomContextMenu);
        connect(file_view_, SIGNAL(customContextMenuRequested(const QPoint&)), this, SLOT(show_file_menu(const QPoint&)));

        layout_ = new QVBoxLayout(this);
        layout_->addWidget(file_view_);
    }

    void create_file() {
        QModelIndex index = file_view_->currentIndex();
        if (!index.isValid()) {
            return;
        }

        QString path = file_model_->filePath(index);
        if (file_model_->isDir(index)) {
            path = path + "/untitled.txt";
        } else {
            path = path + ".txt";
        }

        QFile file(path);
        if (file.exists()) {
            return;
        }

        if (file.open(QFile::WriteOnly)) {
            QTextStream stream(&file);
            stream << "";
            file.close();
        }

        file_model_->setRootPath("");
        file_model_->setRootPath(QDir::rootPath());
    }

    void create_folder() {
        QModelIndex index = file_view_->currentIndex();
        if (!index.isValid()) {
            return;
        }

        QString path = file_model_->filePath(index);
        path = path + "/untitled";

        QDir dir(path);
        if (dir.exists()) {
            return;
        }

