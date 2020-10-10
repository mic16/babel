#include "backend.hpp"

BackEnd *BackEnd::singleton = nullptr;

void BackEnd::update()
{
    if (isAuth()) {
        int count = 0;
        m_friendlist = m_com->getFriends();
        m_teamlist = m_com->getTeams();
        m_notiflist = m_com->getFriendRequests();

        if (m_onPending) {
            count = m_com->getAcceptCall();
            if (count == 0) {
                m_inCall = true;
                m_onPending = false; // TODO APPELER L'AUDIO START
                callfriend.setFriend(QHostAddress(QString::fromStdString(m_com->getUserIP())));
                audio->start();
            }
            if (count == 1) {
                m_inCall = false;
                m_onPending = false;
            }
        }
        else {
            std::string name = m_com->getCall();
            if (name.compare("") != 0) {
                m_calledFriend = name;
                m_onPopup = true;
            }
        }
        emit notifListChanged();
    }
}

BackEnd::BackEnd(QObject *parent) :
    QObject(parent)
{
    m_microphone = true;
    m_com = new Communication;
    m_quit = false;
    m_onPending = false;
    m_inCall = false;
    m_onPopup = false;
    audio = new PortAudio(48000, 256, 2);
    audio->setCallback(this);
    // m_thread_obj = std::thread(thread_func, this);
}

void BackEnd::firstUpdate()
{
    std::cout << "JE REMPLIS LA FRIEDN LIST UNE PREMIERE FOIS" << std::endl;
    m_friendlist = m_com->getFriends();
    std::cout << "CA ME RENVOI CA " << m_friendlist[0] << std::endl;
    m_teamlist = m_com->getTeams();
    m_notiflist = m_com->getFriendRequests();
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

QString BackEnd::callerName()
{
    return QString::fromStdString(m_calledFriend);
}

QString BackEnd::passWord()
{
    return QString::fromStdString(m_passWord);
}

QList<QString> BackEnd::friendlist()
{
    QList<QString> list;

    std::cout << "JE GET MA FRIEND LIST avec " << m_friendlist[0] << " et " << m_friendlist.size() << std::endl;
    for (size_t i = 0; i < m_friendlist.size(); i++)
        list.append(QString::fromStdString(m_friendlist[i]));
    std::cout << "JE GET MA QQQQQQQQQFRIEND LIST avec " << list.size() << std::endl;
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
    std::string username = userName.toUtf8().constData();
    if (username == m_userName)
        return;

    m_userName = username;
    emit userNameChanged();
}

int BackEnd::getFriendlistSize()
{
    return m_friendlist.size();
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

void BackEnd::setCallerName(const QString &name)
{
    std::string Name = name.toUtf8().constData();
    if (Name == m_calledFriend)
        return;

    m_calledFriend = Name;
}

void BackEnd::addToFriendlist(const QString &friendName)
{
    std::string friendNameString = friendName.toUtf8().constData();
    if (std::find(m_friendlist.begin(), m_friendlist.end(), friendNameString) != m_friendlist.end())
        return;
    m_friendlist.push_back(friendNameString);
    m_com->addFriend(friendNameString);
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

// bool BackEnd::existInTeam(const QString &teamName, const QString &friendName)
// {
//     std::string teamname = teamName.toUtf8().constData();
//     std::string friendNameString = friendName.toUtf8().constData();
//     if (std::find(m_teamlist.at(teamname).begin(), m_teamlist.at(teamname).end(), friendNameString) == m_teamlist.at(teamname).end())
//         return false;
//     return true;
// }

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

bool BackEnd::addUserToDataBase(const QString &UserName, const QString &PassWord)
{
    std::string aze = UserName.toStdString();
    std::cout << "AZE EST EGAL A " << aze << std::endl;
    return (m_com->createUser(UserName.toUtf8().constData(), PassWord.toUtf8().constData()));
}

bool BackEnd::isServerOn()
{
    return(m_com->isServerOn());
}

bool BackEnd::getOnPending()
{
    return m_onPending;
}

bool BackEnd::getOnPopup()
{
    return m_onPopup;
}

void BackEnd::removeFriendDataBase(const QString &userName) // add to qml
{
    m_com->removeFriend(userName.toUtf8().constData());
}

void BackEnd::addMembersTeamListDatabase(const QString &teamname, const QString &username) // add to qml
{
    m_com->addUserToTeam(username.toUtf8().constData(), teamname.toUtf8().constData());
}

void BackEnd::removeMembersTeamListDatabase(const QString &teamname, const QString &username) // add to qml
{
    m_com->removeUserFromTeam(username.toUtf8().constData(), teamname.toUtf8().constData());
}

void BackEnd::callFriend(const QString &Name)
{
    // TODO FAIRE LA REQUETE D'APEL A UN AMI
    m_com->callUser(Name.toUtf8().constData());
    m_onPending = true;
    m_calledFriend = Name.toUtf8().constData();
}

void BackEnd::hangUpFriend()
{
    m_com->hangUpFriend();
    audio->stop();
}

bool BackEnd::callTeam(const QString &Name)
{
    // TODO FAIRE LA REQUETE D'APEL A UNE TEAM
    return false;
}

void BackEnd::callAccept(bool bool_accept)
{
    m_com->acceptCall(bool_accept);
    if (bool_accept) {
        callfriend.setFriend(QHostAddress(QString::fromStdString(m_com->getUserIP())));
        audio->start();
    }
    // TODO DIRE AU SERVEUR SI LE CALL EST ACCEPTER
}

void BackEnd::disconnect()
{
    // TODO LE DISCONNECT
    std::cout << "AAAAAAAAAAAA" << std::endl;
    m_quit = true;
    // m_thread_obj.join();
    std::cout << "WOAAW" << std::endl;
    // m_com->disconnect();
    std::cout << "FIN" << std::endl;
    audio->stop();
}

bool BackEnd::isAuth() // add to qml
{
    std::cout << m_userName.compare("") << " - " << m_passWord.compare("") << std::endl;
    if (m_userName.compare("") != 0 && m_passWord.compare("") != 0) {
        std::cout << "HELLO WORLD ENCULER" << std::endl;
        return true;
    }
    return false;
}

bool BackEnd::getQuit()
{
    return m_quit;
}

Communication *BackEnd::getCom()
{
    return m_com;
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

int BackEnd::onAudioReady(const float *inputSamples, unsigned long samplesCount)
{
    callfriend.write(inputSamples, samplesCount);
    return (0);
}

int BackEnd::onAudioNeeded(float *outputSamples, unsigned long samplesCount)
{
    std::memcpy(outputSamples, callfriend.read(samplesCount), samplesCount * sizeof(float));
    return (0);
}

