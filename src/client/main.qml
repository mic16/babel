import QtQuick 2.14
import QtQuick.Window 2.14
import QtQuick.Controls 2.14
import QtQuick.Controls.Material 2.12
import QtQuick.Layouts 1.3
import my.own.backend 1.0

Window {
    id: window
    width: 900
    minimumWidth: 900
    maximumWidth: 900
    height: 600
    minimumHeight: 600
    maximumHeight: 600
    visible: true
    title: qsTr("Babel")
    property var global_i: 0
    property var is_on: false
    property var listTeamMembersName: [[]]
    property var on_call: false
    Material.theme: Material.Dark
    Material.accent: Material.Orange
    flags: Qt.CustomizeWindowHint | Qt.WindowTitleHint

    BackEnd {
        id:backend
        onUserNameChanged: {
            console.log("L'USERNAME EST CHANGED")
        }
        onFriendlistRemoveChanged: {
            console.log("FRIEND LIST HAS REMOVE")
        }
        onFriendlistAddChanged: {
            console.log("FRIEND LIST HAS ADD", addFriendTextField.text)
            backend.addFriendDataBase(addFriendTextField.text)
        }
        onFriendlistChanged: {
        }
        onTeamlistChanged: {
            console.log("TEAM LIST HAS CHANGED")
        }
    }

    Pane {
        id: homePane
        visible: false
        anchors.fill: parent

        Button {
            id: homeButton
            x: 0
            y: -17
            width: 226
            height: 78
            visible: true
            anchors.top: parent.top
            anchors.topMargin: -12
            onClicked: {
                contactFrame.visible = false
                teamFrame.visible = false
                is_on = false
                homeFrame.visible = true
                notiFrame.visible = false
            }
            enabled: true
            Material.background: Material.Amber
        }

        Text {
            id: babelText
            x: 46
            y: -5
            width: 135
            height: 63
            color: "#ffffff"
            text: qsTr("Babel")
            font.pixelSize: 50
            fontSizeMode: Text.FixedSize
            minimumPointSize: 12
            minimumPixelSize: 12
        }


        Frame {
            id: contactListFrame
            x: 0
            width: 226
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            anchors.topMargin: 111
            anchors.bottomMargin: 72


            StackLayout {
                x: 0
                y: 0
                width: 202
                height: 369
                currentIndex: tabBar.currentIndex
                ListView {
                    id: contactList
                    x: 0
                    y: -24
                    width: 202
                    flickableDirection: Flickable.VerticalFlick
                    boundsBehavior: Flickable.StopAtBounds
                    model: contactModel
                    delegate: ItemDelegate {
                        text: model.text
                        width: parent.width

                        highlighted: {
                            if ((is_on === true && teamAddMembersButton.checked === false) || on_call) {
                                console.log("J'HIGHLIGHT")
                                return contactList.currentIndex === index
                            } else
                                return false
                        }
                        onClicked: {
                            if (teamAddMembersButton.checked === true) {
                                console.log("CRASH ?")
                                if (listTeamMembersName[teamList.currentIndex].indexOf(contactModel.get(index).text) !== -1) {
                                    console.log("Atest 1")
                                    listTeamMembersName[teamList.currentIndex] = listTeamMembersName[teamList.currentIndex].filter(r => r !== contactModel.get(index).text)
                                    console.log("Atest 2")
                                    backend.removeMembersToTeamlist(teamModel.get(teamList.currentIndex).text, contactModel.get(index).text)
                                    console.log("Atest 3")
                                    this.highlighted = false
                                } else {
                                    console.log("Btest 1")
                                    listTeamMembersName[teamList.currentIndex].push(contactModel.get(index).text)
                                    console.log("Btest 2")
                                    backend.addMembersToTeamlist(teamModel.get(teamList.currentIndex).text, contactModel.get(index).text)
                                    console.log("Btest 3")
                                    this.highlighted = true
                                }
                                return
                            }
                            console.log(on_call, " is ", callName.text, " and ", contactModel.get(index).text)
                            if (on_call && callName.text === contactModel.get(index).text) {
                                callFrame.visible = true
                                contactFrame.visible = false
                                console.log("SUR LE CALL")
                                contactList.currentIndex = index
                                teamFrame.visible = false
                            } else {
                                teamFrame.visible = false
                                homeFrame.visible = false
                                notiFrame.visible = false
                                callFrame.visible = false
                                is_on = true
                                contactList.currentIndex = index
                                contactNameText.text = contactModel.get(index).text
                                contactFrame.visible = true
                                global_i = index
                                removeFriendButton.enabled = true
                                if (index === 0) {
                                    callButton.enabled = false
                                    removeFriendButton.enabled = false
                                } else if (on_call === false)
                                       callButton.enabled = true
                            }
                        }
                    }
                    ScrollBar.vertical: ScrollBar {}
                }

                ListView {
                    id: teamList
                    x: 0
                    y: -24
                    width: 202
                    flickableDirection: Flickable.VerticalFlick
                    boundsBehavior: Flickable.StopAtBounds
                    model: teamModel
                    delegate: ItemDelegate {
                        text: model.text
                        width: parent.width
                        highlighted: {
                            if (is_on === true || on_call) {
                                return teamList.currentIndex === index
                            } else
                                return false
                        }
                        onClicked: {
                            if (on_call && callName.text === teamModel.get(index).text) {
                                callFrame.visible = true
                                teamFrame.visible = false
                                contactFrame.visible = false
                                console.log("SUR LE CALL")
                                teamList.currentIndex = index
                            } else {
                                callFrame.visible = false
                                homeFrame.visible = false
                                contactFrame.visible = false
                                notiFrame.visible = false
                                is_on = true
                                teamList.currentIndex = index
                                teamNameText.text = teamModel.get(index).text
                                teamFrame.visible = true
                                global_i = index
                                removeFriendButton.enabled = true
                            }
                        }
                    }
                    ScrollBar.vertical: ScrollBar {}
                }
            }

            TabBar {
                id: tabBar
                x: -12
                y: -61
                width: 226
                height: 46

                TabButton {
                    id: contactTabButton
                    x: 0
                    y: 7
                    width: 107
                    height: 45
                    text: qsTr("Contact")
                }

                TabButton {
                    id: teamTabButton
                    x: 108
                    y: 2
                    width: 117
                    height: 45
                    text: qsTr("Team")
                }
            }
        }

        Frame {
            id: addFriendFrame
            x: 272
            y: 0
            width: 332
            height: 52
            anchors.horizontalCenter: parent.horizontalCenter

            Button {
                id: addFriendButton
                x: 268
                y: -11
                width: 40
                height: 51
                icon.source: "../../assets/add-friend.png"
                display: AbstractButton.IconOnly
                onClicked: {
                    if (addFriendTextField.text === "")
                        return
                    backend.addToFriendlist(addFriendTextField.text)
                    contactModel.append(({text: addFriendTextField.text}))
                    addFriendTextField.clear()
                }
            }

            TextField {
                id: addFriendTextField
                x: 0
                y: -3
                width: 252
                height: 43
                placeholderText: qsTr("Friend Pseudonyme")
                maximumLength: 14
                selectByMouse: true
                onFocusChanged: {
                    if (this.focus === false) {
                        if (addFriendButton.focus === true) {
                            this.focus = true
                        } else {
                            this.focus = false
                        }
                    }
                }
            }
        }
        Frame {
            id: addTeamFrame
            x: 274
            y: 0
            width: 332
            height: 52
            visible: false
            anchors.horizontalCenterOffset: 0
            anchors.horizontalCenter: parent.horizontalCenter
            Button {
                id: addTeamButton
                x: 268
                y: -11
                width: 40
                height: 51
                display: AbstractButton.IconOnly
                icon.source: "../../assets/add-group.png"
                onClicked: {
                    if (addTeamText.text === "")
                        return
                    backend.addToTeamlist(addTeamText.text)
                    teamModel.append(({text: addTeamText.text}))
                    listTeamMembersName.push([])
                    addTeamText.clear()
                    addTeamFrame.visible = false
                    addFriendFrame.visible = true
                    teamSwitchButton.text = qsTr("Create Team")
                }
            }

            TextField {
                id: addTeamText
                x: 0
                y: -3
                width: 252
                height: 43
                placeholderText: qsTr("Team name")
                maximumLength: 14
                selectByMouse: true
                onFocusChanged: {
                    if (this.focus === false) {
                        if (addTeamButton.focus === true) {
                            this.focus = true
                        } else {
                            this.focus = false
                        }
                    }
                }
            }
        }

        Button {
            id: teamSwitchButton
            x: 625
            y: 2
            text: qsTr("Create Team")
            onClicked: {
                if (this.text === qsTr("Create Team")) {
                    addTeamFrame.visible = true
                    addFriendFrame.visible = false
                    this.text = qsTr("Cancel")
                } else if (this.text === qsTr("Cancel")) {
                    addTeamFrame.visible = false
                    addFriendFrame.visible = true
                    this.text = qsTr("Create Team")
                }
            }
        }


        ListModel {
            id: contactModel
            ListElement {
                text: ""
            }
        }
        ListModel {
            id: teamModel
            ListElement {
                text: ""
            }
        }

        RoundButton {
            id: exitButton
            x: 10
            y: 510
            width: 206
            height: 58
            text: "Exit"
            font.pixelSize: 20
            font.capitalization: Font.MixedCase
            font.family: "Ubuntu"
            focusPolicy: Qt.StrongFocus
            Material.background: Material.Red
            onClicked: {
                window.close()
                backend.disconnect()
            }
        }

        Frame {
            id: contactFrame
            visible: false
            anchors.fill: parent
            anchors.rightMargin: 0
            anchors.bottomMargin: 8
            anchors.leftMargin: 239
            anchors.topMargin: 64

            Text {
                id: contactNameText
                x: 0
                y: 22
                width: 613
                height: 65
                text: ""
                color: "#ffffff"
                font.pixelSize: 50
                horizontalAlignment: Text.AlignHCenter
                lineHeightMode: Text.ProportionalHeight
                fontSizeMode: Text.FixedSize
                textFormat: Text.AutoText
                font.hintingPreference: Font.PreferDefaultHinting
            }

            RoundButton {
                id: callButton
                x: 213
                y: 241
                width: 188
                height: 88
                Material.background: Material.Green
                font.capitalization: Font.MixedCase
                onClicked: {
                    on_call = true
                    callButton.enabled = false
                    teamCallButton.enabled = false
                    callFrame.visible = true
                    callName.text = contactNameText.text
                    contactFrame.visible = false
                    backend.callFriend(callName.text)
                }

                Text {
                    id: callText
                    x: 63
                    y: 30
                    width: 106
                    height: 34
                    color: "#ffffff"
                    text: "Call"
                    font.pixelSize: 25
                    horizontalAlignment: Text.AlignHCenter
                    lineHeightMode: Text.ProportionalHeight
                    fontSizeMode: Text.FixedSize
                    font.hintingPreference: Font.PreferDefaultHinting
                    textFormat: Text.AutoText
                }

                Image {
                    id: callImg
                    x: 32
                    y: 19
                    width: 48
                    height: 49
                    source: "../../assets/phone-call.png"
                }
            }

            RoundButton {
                id: removeFriendButton
                x: 213
                y: 358
                width: 188
                height: 88
                text: "Remove Friend"
                font.capitalization: Font.MixedCase
                Material.background: Material.Blue
                onClicked: {
                    backend.removeToFriendlist(contactModel.get(contactList.currentIndex).text)
                    contactModel.remove(global_i)
                    contactFrame.visible = false
                    // TODO Remove friend signal function
                }
            }
        }

        Frame {
            id: homeFrame
            visible: true
            anchors.fill: parent
            Text {
                id: homeText
                x: 0
                y: 0
                width: 613
                height: 65
                color: "#ffffff"
                text: "Home"
                font.pixelSize: 50
                horizontalAlignment: Text.AlignHCenter
                lineHeightMode: Text.ProportionalHeight
                fontSizeMode: Text.FixedSize
                font.hintingPreference: Font.PreferDefaultHinting
                textFormat: Text.AutoText
            }

            Text {
                id: homeTextPlain
                x: 23
                y: 71
                width: 567
                height: 385
                text: "This the home of the Babel program !\nHere you have some information about it:\n\n- At the top right you have switch that allow you change between two style, \nLight and Dark\n- At the top left you have the Babel text which when you click on it,\nyou get here on the home page\n- Between those button is the bar to search other user and add them by\ntheir username\n- Just right from the friand bar, you have the button to create a team\n-At the left you have all the contacts you've add, you can click on each\nof them to call them or remove them from the list\n-At the bottom left you have the button to quit the program, easy\n-And at the center is the main page where you'll see all information\nlike what you are reading right now, or your friend when you click on them"
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                color: "#ffffff"
            }
            anchors.leftMargin: 239
            anchors.rightMargin: 0
            anchors.bottomMargin: 8
            anchors.topMargin: 64
        }

        Frame {
            id: teamFrame
            visible: false
            anchors.fill: parent
            anchors.leftMargin: 239
            anchors.rightMargin: 0
            anchors.topMargin: 64
            anchors.bottomMargin: 8
            Text {
                id: teamNameText
                x: 0
                y: 22
                width: 613
                height: 65
                color: "#ffffff"
                text: ""
                font.pixelSize: 50
                horizontalAlignment: Text.AlignHCenter
                lineHeightMode: Text.ProportionalHeight
                fontSizeMode: Text.FixedSize
                textFormat: Text.AutoText
                font.hintingPreference: Font.PreferDefaultHinting
            }

            RoundButton {
                id: teamCallButton
                x: 213
                y: 173
                width: 188
                height: 88
                font.capitalization: Font.MixedCase
                onClicked: {
                    on_call = true
                    callFrame.visible = true
                    callName.text = teamNameText.text
                    teamFrame.visible = false
                    backend.callTeam(callName.text)
                }

                Text {
                    id: callText1
                    x: 63
                    y: 30
                    width: 106
                    height: 34
                    color: "#ffffff"
                    text: "Call"
                    font.pixelSize: 25
                    horizontalAlignment: Text.AlignHCenter
                    lineHeightMode: Text.ProportionalHeight
                    fontSizeMode: Text.FixedSize
                    textFormat: Text.AutoText
                    font.hintingPreference: Font.PreferDefaultHinting
                }

                Image {
                    id: callImg1
                    x: 32
                    y: 19
                    width: 48
                    height: 49
                    source: "../../assets/phone-call.png"
                }
                Material.background: Material.Green
            }

            RoundButton {
                id: removeTeamButton
                x: 213
                y: 387
                width: 188
                height: 88
                text: "Remove Team"
                font.capitalization: Font.MixedCase
                Material.background: Material.Blue
                onClicked: {
                    backend.removeToTeamlist(teamModel.get(teamList.currentIndex).text)
                    teamModel.remove(teamList.currentIndex)
                    teamFrame.visible = false
                }
            }

            RoundButton {
                id: teamAddMembersButton
                x: 213
                y: 280
                width: 188
                height: 88
                checkable: true
                text: "Add Members to Team"
                font.capitalization: Font.MixedCase
                Material.background: Material.Purple
                onCheckedChanged: {
                    console.log(this.checked)
                    tabBar.currentIndex = 0
                    if (this.checked === true)
                        Material.background = Material.Orange
                    else
                        Material.background = Material.Purple
                }
            }

            Button {
                id: printMembers
                x: 484
                y: 300
                text: qsTr("Members")
                onClicked: {
                    console.log(listTeamMembersName[teamList.currentIndex])
                }
            }
        }

        Frame {
            id: callFrame
            x: 239
            y: 64
            width: 637
            height: 504
            visible: false

            Popup {
                    id: callPopup
                    x: 100
                    y: 100
                    width: 220
                    height: 200
                    modal: true
                    focus: true
                    closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutside
                    onOpened: {
                        callerName.text = callerName.text + "\n\n is calling you !"
                    }

                    Text {
                        id: callerName
                        color: "#ffffff"
                        text: "AAAAAAAAAAAAAA"
                        font.pixelSize: 20
                        width: 220
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                        x: -12
                        y: 0
                    }

                    RoundButton {
                        id: callValidation
                        Material.background: Material.Green
                        icon.source: "../../assets/checked.png"
                        x: 10
                        y: 100
                        width: 75
                        height: 75
                        onClicked: {
                            backend.callAccept(true)
                        }
                    }
                    RoundButton {
                        id: callRefuse
                        Material.background: Material.Red
                        icon.source: "../../assets/cross-sign.png"
                        x: 110
                        y: 100
                        width: 75
                        height: 75
                        onClicked: {
                            backend.callAccept(false)
                            callPopup.close()
                        }
                    }

                }

            RoundButton {
                id: muteCallButton
                x: 94
                y: 340
                width: 188
                height: 88
                font.capitalization: Font.MixedCase
                checkable: true
                onCheckedChanged: {
                    if (checked === true) {
                        muteText.text = "Unmute"
                        backend.microphone = false
                        // TODO SEND A SIGNAL WHEN IT'S MUTE
                    } else {
                        muteText.text = "Mute"
                        backend.microphone = true
                    }
                }

                Text {
                    id: muteText
                    x: 70
                    y: 28
                    width: 106
                    height: 34
                    color: "#ffffff"
                    text: "Mute"
                    font.pixelSize: 25
                    horizontalAlignment: Text.AlignHCenter
                    lineHeightMode: Text.ProportionalHeight
                    font.hintingPreference: Font.PreferDefaultHinting
                    fontSizeMode: Text.FixedSize
                    textFormat: Text.AutoText
                }

                Image {
                    id: muteImg
                    x: 23
                    y: 20
                    width: 48
                    height: 49
                    source: "../../assets/mute.png"
                }
            }

            RoundButton {
                id: disconnectCallButton
                x: 338
                y: 340
                width: 188
                height: 88
                text: "Disconnect"
                font.capitalization: Font.MixedCase
                font.pointSize: 20
                Material.background: Material.Red
                onClicked: {
                    on_call = false
                    callButton.enabled = true
                    teamCallButton.enabled = true
                    if (backend.existingTeam(callName.text)) {
                        callFrame.visible = false
                        teamFrame.visible = true
                    } else {
                        callFrame.visible = false
                        contactFrame.visible = true
                    }
                }
            }

            Text {
                id: callName
                x: 0
                y: 12
                width: 613
                height: 88
                color: "#ffffff"
                font.pixelSize: 62
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                minimumPixelSize: 12
            }

            Button {
                id: printMembers1
                x: 521
                y: 216
                text: qsTr("Members")
                visible: false
                onClicked: {
                    console.log(listTeamMembersName[teamList.currentIndex])
                }
            }
        }

        Frame {
            id: notiFrame
            visible: false
            anchors.fill: parent
            anchors.rightMargin: 0
            anchors.bottomMargin: 8
            anchors.leftMargin: 239
            anchors.topMargin: 64


            ListView {
                id: notifListView
                x: 0
                y: 0
                width: 613
                height: 480
                model: notifModel
                delegate: ItemDelegate {
                    text: model.text
                    width: parent.width
                    highlighted: {
                        return notifListView.currentIndex === index
                    }
                    onClicked: {
                        if (notifModel.count === 0) {
                            addButton.visible = false
                            refuseButton.visible = false
                        } else {
                            addButton.visible = true
                            refuseButton.visible = true
                        }
                        addButton.y = index * 48
                        refuseButton.y = index * 48
                        notifListView.currentIndex = index
                        // TODO LIMIT OF MODEL IS 10 !!!
                    }
                }
            }

            ListModel {
                id: notifModel
                ListElement {
                    text: ""
                }

            }

            Button {
                id: addButton
                x: 418
                y: 0
                icon.source: "../../assets/checked.png"
                display: AbstractButton.IconOnly
                Material.background: Material.Green
                onClicked: {
                    contactModel.append(({text: notifModel.get(notifListView.currentIndex).text}))
                    backend.addToFriendlist(notifModel.get(notifListView.currentIndex).text)
                    notifModel.remove(notifListView.currentIndex)
                    if (notifModel.count === 0) {
                        addButton.visible = false
                        refuseButton.visible = false
                    } else {
                        addButton.visible = true
                        refuseButton.visible = true
                    }
                    // TODO SEND SIGNAL ACCEPT
                }
            }

            Button {
                id: refuseButton
                x: 536
                y: 0
                icon.source: "../../assets/cross-sign.png"
                display: AbstractButton.IconOnly
                Material.background: Material.Red
                onClicked: {
                    notifModel.remove(notifListView.currentIndex)
                    if (notifModel.count === 0) {
                        addButton.visible = false
                        refuseButton.visible = false
                    } else {
                        addButton.visible = true
                        refuseButton.visible = true
                    }
                    // TODO SEND SIGNAL REFUSE
                }
            }
        }

        RoundButton {
            id: notifButton
            x: 740
            y: 25
            width: 64
            height: 41
            icon.source: "../../assets/notification.png"
            display: AbstractButton.IconOnly
            onClicked: {
                notiFrame.visible = true
                contactFrame.visible = false
                teamFrame.visible = false
                homeFrame.visible = false
                if (notifModel.count === 0) {
                    addButton.visible = false
                    refuseButton.visible = false
                } else {
                    addButton.visible = true
                    refuseButton.visible = true
                }
//                backend.display()
                callerName.text = "AAAAAAAAAAAAAA"
                callPopup.open()
            }
        }

    }


    Pane {
        id: pseudoPane
        visible: true
        anchors.fill: parent
        anchors.rightMargin: 0
        anchors.bottomMargin: 0
        anchors.leftMargin: 0
        anchors.topMargin: 0
        clip: false

        Text {
            id: pseudoText1
            x: 107
            y: 15
            color: "#ffffff"
            width: 639
            height: 75
            text: qsTr("Babel")
            font.pixelSize: 50
            horizontalAlignment: Text.AlignHCenter
        }

        GroupBox {
            id: registerGroupBox
            x: 496
            y: 169
            width: 357
            height: 378
            title: qsTr("")

            TextField {
                id: pseudoRegisterTextField
                height: 48
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.top: parent.top
                horizontalAlignment: Text.AlignHCenter
                anchors.rightMargin: 9
                anchors.leftMargin: 101
                anchors.topMargin: 40
                placeholderText: qsTr("Ex: Guest")
                maximumLength: 14
                selectByMouse: true
                onFocusChanged: {
                    if (pseudoRegisterTextField.focus === true)
                        registerButton.Material.background = Material.Blue
                }
            }

            Button {
                id: registerButton
                height: 55
                text: qsTr("Sign up")
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.top: parent.top
                anchors.leftMargin: 89
                anchors.rightMargin: 89
                anchors.topMargin: 268
                font.capitalization: Font.MixedCase
                Material.background: Material.Blue
                onClicked: {
                    if (backend.isServerOn() === false) {
                        //TODO PUT RED BANNER
                        return
                    }
                    if (pseudoRegisterTextField.text === "" || pseudoRegisterTextField.text.replace(" ", "") === "" || passwordRegisterTextField.text !== passwordRegisterValidTextField.text || passwordRegisterTextField.text === "" || passwordRegisterTextField.text.replace(" ", "") === "" || backend.addUserToDataBase() === false) {
                        registerButton.Material.background = Material.Red
                        passwordRegisterValidTextField.Material.accent = Material.Red
                        return

                    } else {
                        pseudoPane.visible = false
                        homePane.visible = true
                    }
                    if (contactModel.get(0).text === "") {
                        contactModel.clear()
                        contactModel.append(({text: pseudoRegisterTextField.text}))
                        backend.userName = pseudoRegisterTextField.text
                        backend.passWord = passwordRegisterTextField.text
                    }
                    teamModel.clear()
                    notifModel.clear()
                    // if (backend.addUserToDataBase())
                    //     console.log("J'AI CREER MON USER")
                    // else
                    //     console.log("J'AI PAS CREER MON USER")
                }
            }

            Text {
                id: text2
                x: 0
                y: 50
                width: 82
                height: 28
                color: "#ffffff"
                text: qsTr("Username:")
                font.pixelSize: 17
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }

            TextField {
                id: passwordRegisterTextField
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.top: parent.top
                horizontalAlignment: Text.AlignHCenter
                placeholderText: qsTr("")
                maximumLength: 14
                anchors.leftMargin: 101
                anchors.rightMargin: 9
                anchors.topMargin: 126
                echoMode: TextInput.Password
                onFocusChanged: {
                    if (passwordRegisterTextField.focus === true)
                        registerButton.Material.background = Material.Blue
                }
            }

            Text {
                id: text3
                x: 0
                y: 126
                width: 82
                height: 28
                color: "#ffffff"
                text: qsTr("Password:")
                font.pixelSize: 17
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }

            TextField {
                id: passwordRegisterValidTextField
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.top: parent.top
                horizontalAlignment: Text.AlignHCenter
                placeholderText: qsTr("")
                maximumLength: 14
                anchors.leftMargin: 101
                anchors.rightMargin: 9
                anchors.topMargin: 195
                echoMode: TextInput.Password
                onFocusChanged: {
                    if (passwordRegisterValidTextField.focus === true)
                        registerButton.Material.background = Material.Blue
                }
            }

            Text {
                id: text4
                x: 0
                y: 202
                width: 82
                height: 28
                color: "#ffffff"
                text: qsTr("Password:")
                font.pixelSize: 17
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }
        }

        GroupBox {
            id: signinGroupBox
            x: 40
            y: 242
            width: 357
            height: 268
            title: qsTr("")
            TextField {
                id: pseudoSigninTextField
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.top: parent.top
                horizontalAlignment: Text.AlignHCenter
                placeholderText: qsTr("Ex: Guest")
                maximumLength: 14
                anchors.leftMargin: 101
                anchors.rightMargin: 9
                anchors.topMargin: 40
                selectByMouse: true
            }

            Button {
                id: signinButton
                text: qsTr("Sign in")
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.top: parent.top
                anchors.leftMargin: 92
                font.capitalization: Font.MixedCase
                anchors.rightMargin: 92
                anchors.topMargin: 184
                Material.background: Material.Green
                onClicked: {
                    teamModel.clear()
                    notifModel.clear()
                    if (backend.isServerOn() === false) {
                        //TODO PUT RED BANNER
                        return
                    }
                    if (backend.existingCredential(pseudoSigninTextField.text, passwordSigninTextField.text)) {
                        pseudoPane.visible = false
                        homePane.visible = true
                        if (contactModel.get(0).text === "") {
                            contactModel.clear()
                            contactModel.append(({text: pseudoSigninTextField.text}))
                            backend.fillUserInfo() // friend list, team list, etc....
                            backend.userName = pseudoSigninTextField.text
                            backend.passWord = passwordRegisterTextField.text
                        }
                    }
                    // TODO GET TOUTE LES INFO USERS
                }
            }

            Text {
                id: text5
                x: 0
                y: 50
                width: 82
                height: 28
                color: "#ffffff"
                text: qsTr("Username:")
                font.pixelSize: 17
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }

            TextField {
                id: passwordSigninTextField
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.top: parent.top
                horizontalAlignment: Text.AlignHCenter
                placeholderText: qsTr("")
                maximumLength: 14
                anchors.leftMargin: 101
                anchors.rightMargin: 9
                anchors.topMargin: 108
                echoMode: TextInput.Password
            }

            Text {
                id: text6
                x: 0
                y: 127
                width: 82
                height: 28
                color: "#ffffff"
                text: qsTr("Password:")
                font.pixelSize: 17
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }
        }

        Text {
            id: pseudoText2
            x: 40
            y: 161
            width: 357
            height: 75
            color: "#ffffff"
            text: qsTr("Already have an account ?\nSign in now !")
            font.pixelSize: 25
            horizontalAlignment: Text.AlignHCenter
        }

        Text {
            id: pseudoText3
            x: 496
            y: 88
            width: 357
            height: 65
            color: "#ffffff"
            text: qsTr("Don't have account ?\nRegister here")
            font.pixelSize: 25
            horizontalAlignment: Text.AlignHCenter
        }

    }

    Switch {
        id: themeSwitch
        x: 769
        y: 0
        text: qsTr("Light/Dark")
        anchors.right: parent.right
        anchors.rightMargin: 0
        checked: true
        onCheckedChanged: {
            if (window.Material.theme === Material.Light) {
                window.Material.theme = Material.Dark
                babelText.color = "#ffffff"
                contactNameText.color = "#ffffff"
                callText.color = "#ffffff"
                pseudoText1.color = "#ffffff"
                pseudoText2.color = "#ffffff"
                pseudoText3.color = "#ffffff"
                text2.color = "#ffffff"
                text3.color = "#ffffff"
                text4.color = "#ffffff"
                text5.color = "#ffffff"
                text6.color = "#ffffff"
                homeText.color = "#ffffff"
                homeTextPlain.color = "#ffffff"
                teamNameText.color = "#ffffff"
                callText1.color = "#ffffff"
            } else {
                window.Material.theme = Material.Light
                babelText.color = "#000000"
                contactNameText.color = "#000000"
                callText.color = "#000000"
                pseudoText1.color = "#000000"
                pseudoText2.color = "#000000"
                pseudoText3.color = "#000000"
                text2.color = "#000000"
                text3.color = "#000000"
                text4.color = "#000000"
                text5.color = "#000000"
                text6.color = "#000000"
                homeText.color = "#000000"
                homeTextPlain.color ="#000000"
                teamNameText.color = "#000000"
                callText1.color = "#000000"
            }
        }
    }
}
