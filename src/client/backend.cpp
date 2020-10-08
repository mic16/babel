#include "backend.hpp"

BackEnd *BackEnd::singleton = nullptr;

void thread_func(BackEnd *backend)
{
    int aze = 0;

    while (true) {
        std::cout << aze << std::endl;
        aze += 1;
        if (backend->getQuit())
            break;
    }
}

BackEnd::BackEnd(QObject *parent) :
    QObject(parent)
{
    m_microphone = true;
    m_com = new Communication;
    m_quit = false;
    m_thread_obj = std::thread(thread_func, this);
}

BackEnd *BackEnd::get(QObject *parent)
{
    if (!singleton)
        singleton = new BackEnd(parent);
    return singleton;
}

QString BackEnd::userName()
{
    return QString::fromStdString(m_userName);
}

QString BackEnd::passWord()
{
    return QString::fromStdString(m_passWord);
}

QList<QString> BackEnd::friendlist()
{
    QList<QString> list;

    for (size_t i = 0; i < m_friendlist.size(); i++)
        list.append(QString::fromStdString(m_friendlist[i]));
    return list;
}

QMap<QString, QList<QString>> BackEnd::teamlist()
{
    QMap<QString, QList<QString>> list;
    std::map<std::string, std::vector<std::string>>::iterator it;
    std::vector<std::string>::iterator vit;


    for (it = m_teamlist.begin(); it != m_teamlist.end(); it++) {
        QList<QString> tmpList;
        for (vit = it->second.begin(); vit != it->second.end(); vit++) {
            tmpList.append(QString::fromStdString(*vit));
        }
        list.insert(QString::fromStdString(it->first), tmpList);
    }
    return list;
}

bool BackEnd::microphone()
{
    return m_microphone;
}

void BackEnd::setUserName(const QString &userName)
{
    m_quit = true;
    std::string username = userName.toUtf8().constData();
    if (username == m_userName)
        return;

    m_userName = username;
    emit userNameChanged();
}

void BackEnd::setpassWord(const QString &passWord)
{
    std::string password = passWord.toUtf8().constData();
    if (password == m_passWord)
        return;

    m_passWord = password;
    emit passWordChanged();
}

void BackEnd::setMicrophone(const bool &microphone)
{
    if (microphone == m_microphone)
        return;

    m_microphone = microphone;
    emit microphoneChanged();
}

void BackEnd::addToFriendlist(const QString &friendName)
{
    std::string friendNameString = friendName.toUtf8().constData();
    if (std::find(m_friendlist.begin(), m_friendlist.end(), friendNameString) != m_friendlist.end())
        return;
    m_friendlist.push_back(friendNameString);
    emit friendlistAddChanged();
    emit friendlistChanged();
}

void BackEnd::removeToFriendlist(const QString &friendName)
{
    std::string friendNameString = friendName.toUtf8().constData();
    if (std::find(m_friendlist.begin(), m_friendlist.end(), friendNameString) != m_friendlist.end() == false)
        return;
    std::cout << "je supprime l'ami " << friendNameString << std::endl;
    m_friendlist.erase(std::find(m_friendlist.begin(), m_friendlist.end(), friendNameString));
    emit friendlistRemoveChanged();
    emit friendlistChanged();
}

void BackEnd::addToTeamlist(const QString &teamName)
{
    std::string teamname = teamName.toUtf8().constData();
    if (m_teamlist.find(teamname) != m_teamlist.end())
        return;
    m_teamlist.insert({teamname, std::vector<std::string>()});
    m_com->createTeam(teamname);
    emit teamlistChanged();
    emit teamlistAddChanged();
}

void BackEnd::removeToTeamlist(const QString &teamName)
{
    std::string teamname = teamName.toUtf8().constData();
    if (m_teamlist.find(teamname) == m_teamlist.end())
        return;
    m_teamlist.erase(teamname);
    // m_com->removeTeam(teamname);
    emit teamlistChanged();
    emit teamlistRemoveChanged();
}

void BackEnd::addMembersToTeamlist(const QString &teamName, const QString &friendName)
{
    std::string teamname = teamName.toUtf8().constData();
    std::string friendNameString = friendName.toUtf8().constData();
    if (m_teamlist.find(teamname) == m_teamlist.end() || (std::find(m_friendlist.begin(), m_friendlist.end(), friendNameString) != m_friendlist.end() == false))
        return;
    std::cout << "j'ajoute " << friendNameString << " a l'équipe " << teamname << std::endl;
    std::vector<std::string> tmpVector = m_teamlist.at(teamname);
    tmpVector.push_back(friendNameString);
    m_teamlist.insert_or_assign(teamname, tmpVector);
    emit teamlistChanged();
    emit teamlistMembersAddChanged();
}

void BackEnd::removeMembersToTeamlist(const QString &teamName, const QString &friendName)
{
    std::string teamname = teamName.toUtf8().constData();
    std::string friendNameString = friendName.toUtf8().constData();
    if (m_teamlist.find(teamname) == m_teamlist.end() || (std::find(m_friendlist.begin(), m_friendlist.end(), friendNameString) != m_friendlist.end() == true))
        return;
    std::vector<std::string>::iterator it = std::find(m_teamlist.at(teamname).begin(), m_teamlist.at(teamname).end(), friendNameString);
    m_teamlist.at(teamname).erase(it);
    emit teamlistChanged();
    emit teamlistMembersRemoveChanged();
}

bool BackEnd::existInTeam(const QString &teamName, const QString &friendName)
{
    std::string teamname = teamName.toUtf8().constData();
    std::string friendNameString = friendName.toUtf8().constData();
    if (std::find(m_teamlist.at(teamname).begin(), m_teamlist.at(teamname).end(), friendNameString) == m_teamlist.at(teamname).end())
        return false;
    return true;
}

bool BackEnd::existingTeam(const QString &Name)
{
    std::string name = Name.toUtf8().constData();
    if (m_teamlist.find(name) == m_teamlist.end())
        return false;
    return true;
}

bool BackEnd::existingCredential(const QString &UserName, const QString &PassWord)
{
    return (m_com->connectUser(UserName.toUtf8().constData(), PassWord.toUtf8().constData()));
}

bool BackEnd::addUserToDataBase()
{
    return (m_com->createUser(m_userName, m_passWord));
}

void BackEnd::fillUserInfo()
{
    m_com->getFriends();
    
    // m_com->getTeams();
    // m_com->getFriendsRequest();
    // TODO REQUETE TO GET ALL USER INFO FROM DATABASE
}

void BackEnd::addFriendDataBase(const QString &userName)
{
    std::cout << "j'add l'ami " << userName.toUtf8().constData() << std::endl;
    std::cout << m_com->addFriend(userName.toUtf8().constData()) << " " << true << std::endl;
}

void BackEnd::removeFriendDataBase(const QString &userName)
{
    m_com->removeFriend(userName.toUtf8().constData());
}

void BackEnd::addMembersTeamListDatabase(const QString &teamname, const QString &username)
{
    m_com->addUserToTeam(username.toUtf8().constData(), teamname.toUtf8().constData());
}

void BackEnd::removeMembersTeamListDatabase(const QString &teamname, const QString &username)
{
    // TODO REQUETE TO UDPATE THE FRIEND LIST IN DATABASE
}

bool BackEnd::callFriend(const QString &Name)
{
    // TODO FAIRE LA REQUETE D'APEL A UN AMI
    return false;
}

bool BackEnd::callTeam(const QString &Name)
{
    // TODO FAIRE LA REQUETE D'APEL A UNE TEAM
    return false;
}

void BackEnd::disconnect()
{
    // TODO LE DISCONNECT
    m_quit = true;
    m_thread_obj.join();
}

bool BackEnd::getQuit()
{
    return m_quit;
}

void BackEnd::display()
{
    std::map<std::string, std::vector<std::string>>::iterator it = m_teamlist.begin();
    std::vector<std::string>::iterator vector_it = m_friendlist.begin();

    std::cout << "My name is " << m_userName << std::endl;
    std::cout << "My friend are :" << std::endl;
    for (; vector_it != m_friendlist.end(); vector_it++) {
        std::cout << "- " << *vector_it << std::endl;
    }
    std::cout << "My teams are: " << std::endl;
    for (; it != m_teamlist.end(); it++) {
        std::cout << "- " << it->first << " with members :" << std::endl;
        std::vector<std::string>::iterator vit = it->second.begin();
        for (; vit != it->second.end(); vit++) {
            std::cout << "    - " << *vit << std::endl;
        }
        std::cout << "]" << std::endl;
    }
}

void BackEnd::alwaysCall()
{
    
    // thread_obj.join();
}