#include <QMainWindow>
#include <QLineEdit>
#include <QComboBox>
#include <QLabel>
#include <QGridLayout>
// #include <string>

using namespace std;

//  ---------------* QT related Declarations * ------------------------- //

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_adminButton_clicked();

    void on_signUpButton_clicked();

    void on_goBackToStartButton_2_clicked();

    void on_signUpButton_2_clicked();

    void on_goBackToLogIn_clicked();

    void on_showPasswordSignUp_checkStateChanged(const Qt::CheckState &checkBox);

    void on_showPasswordConfirmedSignUp_checkStateChanged(const Qt::CheckState &checkBox);

    void on_creditCardNumberLineEdit_textChanged();

    void on_confirmPasswordLineEdit_textChanged();

    void on_stackedWidget_currentChanged(int index);

    void on_passwordLineEdit_textChanged();

    void on_nameOnSignUpLineEdit_textChanged();

    void on_usernameOnSignUpLineEdit_textChanged();

    void on_emailAddressLineEdit_textChanged();

    void on_showPasswordCustomerLoginCheckBox_checkStateChanged(const Qt::CheckState &checkBox);

    void on_passwordAdminLoginCheckBox_checkStateChanged(const Qt::CheckState &checkBox);

    void on_usernameAdminLogInLineEdit_textChanged();

    void on_passwordAdminLogInLineEdit_textChanged();

    void on_usernameCustomerLogInlineEdit_textChanged();

    void on_passwordCustomerLogInlineEdit_textChanged();

    void on_checkAvailableRoomsAtStartButton_clicked();

    void on_checkAvailableRoomsChoiceButton_clicked();

    void on_customerLoginButton_clicked();

    void on_adminLoginButton_clicked();

    void on_goBackFromCheckAvailableRooms_clicked();

    void on_customerLogOutButton_clicked();

    void on_searchForAvailableRoomsButton_clicked();

    void on_checkOutBestRoomsButton_clicked();

    void on_resetSearchResult_clicked();

    void on_reserveRoomChoiceButton_clicked();

    void on_addRoomReviewChoiceButton_clicked();

    void on_reserveRoomButton_clicked();

    void on_goBackFromReserveRoom_clicked();

    void on_goBackFromAddRoomReviewButton_clicked();

    void on_adminLogOutButton_clicked();

    void on_addReservationChoiceButton_clicked();

    void on_editReservationChoiceButton_clicked();

    void on_viewRoomReviewsChoiceButton_clicked();

    void on_toCancelYourReservationButton_clicked();

    void on_confirmReservationCancellation_clicked();

    void on_startDateDayComboBoxReserveRoom_activated();

    void on_startDateMonthComboBoxReserveRoom_activated();

    void on_startDateYearComboBoxReserveRoom_activated();

    void on_endDateDayComboBoxReserveRoom_activated();

    void on_endDateMonthComboBoxReserveRoom_activated();

    void on_endDateYearComboBoxReserveRoom_activated();

    void on_submitRoomReviewButton_clicked();

    void on_customerRoomReviewLineEdit_textEdited();

    void on_customerRoomReviewLineEdit_returnPressed();

    void on_customerIDadminInput_textChanged();

    void on_goBackFromAdminAddReservationButton_clicked();

    void on_adminAddReservationButton_clicked();

    void on_roomNumberAdminInput_textChanged();

    void on_roomNumberLineEditAddReview_textEdited();

    void on_RoomNumberLineEditReserveRoom_textEdited();

    void on_creditCardNumberConfirmationLineEdit_textEdited();

    void on_customerNameFindID_textChanged();

    void on_customerNameFindID_2_textChanged();

    void on_customerIDadminInput_2_textChanged();

    void on_adminEditReservationButton_clicked();

    void on_adminCancelReservationButton_clicked();

    void on_goBackFromEditReservationAdmin_clicked();

    void on_goBackFromViewRoomReviewsChoicesAdmin_clicked();

    void on_signupForCustomer_clicked();

    void on_goBackToViewRoomReviewsChoicesAdmin_clicked();

    void on_goBackToViewRoomReviewsChoicesAdmin_2_clicked();

    void on_goBackToViewRoomReviewsChoicesAdmin_3_clicked();

    void on_allReviewsChoice_clicked();

    void on_unseenReviewsChoice_clicked();

    void on_seenReviewsChoice_clicked();

    void on_lastThirtyDaysChoice_clicked();

    void on_goBackToViewRoomReviewsChoicesAdmin_4_clicked();

private:
    Ui::MainWindow *ui;
    void goToStart();
    void showPasswordCheckBox(const Qt::CheckState &checkBox, QLineEdit* LineEdit);
    void reloadCheckAvailableRooms();
    bool startAndEndDatesEnteredAndValid(
        int startDate[3], int endDate[3],
        QComboBox* startDateDay, QComboBox* startDateMonth, QComboBox* startDateYear,
        QComboBox* endDateDay, QComboBox* endDateMonth, QComboBox* endDateYear,
        QLabel* startDateLabel, QLabel* endDateLabel
    );
    int acceptThreeDigits(QLineEdit* inputLineEdit, int max, int min=0);
    void clearLabelAndPushButtonWidgets(QLayout* layout);
    void displayReviewsWithMarkAsSeenButton(string viewRoomReviewsOutput, QGridLayout* gridLayout);
};

#endif // MAINWINDOW_H