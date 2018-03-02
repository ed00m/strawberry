/*
 * Strawberry Music Player
 * This file was part of Clementine.
 * Copyright 2010, David Sansome <me@davidsansome.com>
 *
 * Strawberry is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Strawberry is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Strawberry.  If not, see <http://www.gnu.org/licenses/>.
 * 
 */

#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include "config.h"

#include <QDialog>
#include <QStyledItemDelegate>

#include "widgets/osd.h"

class QAbstractButton;
class QScrollArea;
class QTreeWidgetItem;

class Application;
class Player;
class Appearance;
class GlobalShortcuts;
class CollectionDirectoryModel;
class SettingsPage;
class Ui_MainWindow;
class Ui_SettingsDialog;

class GstEngine;


class SettingsItemDelegate : public QStyledItemDelegate {
public:
  SettingsItemDelegate(QObject *parent);
  QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const;
  void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
};


class SettingsDialog : public QDialog {
  Q_OBJECT

public:
  SettingsDialog(Application *app, QWidget *parent = nullptr);
  ~SettingsDialog();

  enum Page {
    Page_Behaviour,
    Page_Collection,
    Page_Backend,
    Page_Playback,
    Page_Playlist,
    Page_GlobalShortcuts,
    Page_Appearance,
    Page_Notifications,
    Page_Proxy,
    Page_Transcoding,
  };

  enum Role {
    Role_IsSeparator = Qt::UserRole
  };

  void SetGlobalShortcutManager(GlobalShortcuts *manager) { manager_ = manager; }

  bool is_loading_settings() const { return loading_settings_; }

  Application *app() const { return app_; }
  //Player *player() const { return player_; }
  CollectionDirectoryModel *collection_directory_model() const { return model_; }
  GlobalShortcuts *global_shortcuts_manager() const { return manager_; }
  //const EngineBase *engine() const { return engine_; }
  //const GstEngine *gst_engine() const { return gst_engine_; }
  Appearance *appearance() const { return appearance_; }

  void OpenAtPage(Page page);

  // QDialog
  void accept();
  void reject();

  // QWidget
  void showEvent(QShowEvent *e);

signals:
  void NotificationPreview(OSD::Behaviour, QString, QString);

private slots:
  void CurrentItemChanged(QTreeWidgetItem *item);
  void DialogButtonClicked(QAbstractButton *button);

private:
  struct PageData {
    QTreeWidgetItem *item_;
    QScrollArea *scroll_area_;
    SettingsPage *page_;
  };

  QTreeWidgetItem *AddCategory(const QString &name);
  void AddPage(Page id, SettingsPage *page, QTreeWidgetItem *parent = nullptr);

  void Save();

private:
  Application *app_;
  //Player *player_;
  CollectionDirectoryModel *model_;
  GlobalShortcuts *manager_;
  //const EngineBase *engine_;
  Appearance *appearance_;
  //const GstEngine *gst_engine_;

  Ui_SettingsDialog *ui_;
  //Ui_MainWindow *mui_;
  bool loading_settings_;

  QMap<Page, PageData> pages_;
};

#endif  // SETTINGSDIALOG_H