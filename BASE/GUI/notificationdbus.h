#ifndef NOTIFICATIONDBUS_H
#define NOTIFICATIONDBUS_H

#include <QObject>
#include <QDBusConnection>
#include <QDBusMessage>
#include <QApplication>
#include <QIcon>
#include "notificationdialog.h"
#include "notifications_adaptor.h"
#include "infopanedropdown.h"
#include "tutorialwindow.h"

class NotificationDialog;

class InfoPaneDropdown;

class NotificationDBus : public QObject
{
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", "org.freedesktop.Notifications")
public:
    explicit NotificationDBus(QObject *parent = 0);
    void setDropdownPane(InfoPaneDropdown* pane);

Q_SIGNALS:
    Q_SCRIPTABLE void NotificationClosed(uint id, uint reason);
    Q_SCRIPTABLE void ActionInvoked(uint id, QString action_key);
    void newNotification(int id, QString summary, QString body, QIcon icon);
    void removeNotification(int id);

public Q_SLOTS:
    QStringList GetCapabilities();
    uint Notify(QString app_name, uint replaces_id,
               QString app_icon, QString summary,
               QString body, QStringList actions,
               QVariantMap hints, int expire_timeout);
    void CloseNotification(uint id);
    QString GetServerInformation(QString &vendor,
                              QString &version, QString &spec_version);
    void invokeAction(uint id, QString key);

protected Q_SLOTS:
    void sendCloseNotification(int id, int reason);
    void CloseNotificationUserInitiated(int id);

private:
    QList<NotificationDialog*> dialogs;
    NotificationDialog* currentDialog = NULL;
    int nextId = 1;

    InfoPaneDropdown* dropdownPane = NULL;
    QSettings settings;
};

#endif // NOTIFICATIONDBUS_H
