#include "backend.hpp"

void Backend::printTestString()
{
    std::cout << "xd = " << sampleText << std::endl;
}

bool Backend::loadXmlButtonClicked()
{
    xmlFilePath = QFileDialog::getOpenFileName(nullptr, "Choose a file", "", "All Files (*.*)");
    return xmlFilePath.isEmpty() ? false : true;
}

// case Screen::SET_OWN_TAGS_FOR_UNKNOWN_OPERATIONS:
// {
//     ui->nextPageButton->setVisible(false);
//     cardTransactionCategories = loadMapFromJson(TRANSACTION_TAGS_JSON_FILE);

//     ui->tagsDropDownList->addItem("<wybierz kategorie>");
//     ui->tagsDropDownList->addItem("Zakupy (spozywka)");
//     ui->tagsDropDownList->addItem("Zakupy (inne)");
//     ui->tagsDropDownList->addItem("Rzeczy na mieśćie");
//     ui->tagsDropDownList->addItem("Transport");
//     ui->tagsDropDownList->addItem("Opłaty stałe");
//     ui->tagsDropDownList->addItem("Inne");
//     ui->tagsDropDownList->addItem("Fotografia");

//     loadXmlData();

//     if (!operationsSelfDefined.empty())
//     {
//         operationsSelfDefinedIterator = operationsSelfDefined.begin();
//         ui->operationForSettingTagLabel->setText(
//             QString::fromStdString(operationsSelfDefinedIterator->description));
//     }

//     connect(ui->acceptOperationTag, &QPushButton::clicked, this, [this]()
//             {
//             if (operationsSelfDefinedIterator != operationsSelfDefined.end() && ui->tagsDropDownList->currentIndex() != 0) {
//                 cardTransactionCategories.insert({operationsSelfDefinedIterator->description, ui->tagsDropDownList->currentIndex()});
//                 // ui->tagsDropDownList->setCurrentText("<wybierz kategorie>");
//                 ++operationsSelfDefinedIterator;
//                 if (operationsSelfDefinedIterator != operationsSelfDefined.end()) {
//                     ui->operationForSettingTagLabel->setText(
//                         QString::fromStdString(operationsSelfDefinedIterator->description));
//                 }
//             }else{
//                 ui->nextPageButton->setVisible(true);
//         } });

//     connect(ui->nextPageButton, &QPushButton::clicked, this, &MainWindow::openMainScreen);
//     break;
// }