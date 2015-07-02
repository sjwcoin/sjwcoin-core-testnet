#include "uritests.h"

#include "guiutil.h"
#include "walletmodel.h"

#include <QUrl>

void URITests::uriTests()
{
    SendCoinsRecipient rv;
    QUrl uri;
    uri.setUrl(QString("sjwcoin:fMafLhSZPSfa6iipsC5hW1tuZJYYVDNZa9?req-dontexist="));
    QVERIFY(!GUIUtil::parseBitcoinURI(uri, &rv));

    uri.setUrl(QString("sjwcoin:fMafLhSZPSfa6iipsC5hW1tuZJYYVDNZa9?dontexist="));
    QVERIFY(GUIUtil::parseBitcoinURI(uri, &rv));
    QVERIFY(rv.address == QString("fMafLhSZPSfa6iipsC5hW1tuZJYYVDNZa9"));
    QVERIFY(rv.label == QString());
    QVERIFY(rv.amount == 0);

    uri.setUrl(QString("sjwcoin:fMafLhSZPSfa6iipsC5hW1tuZJYYVDNZa9?label=Wikipedia Example Address"));
    QVERIFY(GUIUtil::parseBitcoinURI(uri, &rv));
    QVERIFY(rv.address == QString("fMafLhSZPSfa6iipsC5hW1tuZJYYVDNZa9"));
    QVERIFY(rv.label == QString("Wikipedia Example Address"));
    QVERIFY(rv.amount == 0);

    uri.setUrl(QString("sjwcoin:fMafLhSZPSfa6iipsC5hW1tuZJYYVDNZa9?amount=0.001"));
    QVERIFY(GUIUtil::parseBitcoinURI(uri, &rv));
    QVERIFY(rv.address == QString("fMafLhSZPSfa6iipsC5hW1tuZJYYVDNZa9"));
    QVERIFY(rv.label == QString());
    QVERIFY(rv.amount == 100000);

    uri.setUrl(QString("sjwcoin:fMafLhSZPSfa6iipsC5hW1tuZJYYVDNZa9?amount=1.001"));
    QVERIFY(GUIUtil::parseBitcoinURI(uri, &rv));
    QVERIFY(rv.address == QString("fMafLhSZPSfa6iipsC5hW1tuZJYYVDNZa9"));
    QVERIFY(rv.label == QString());
    QVERIFY(rv.amount == 100100000);

    uri.setUrl(QString("sjwcoin:fMafLhSZPSfa6iipsC5hW1tuZJYYVDNZa9?amount=100&label=Wikipedia Example"));
    QVERIFY(GUIUtil::parseBitcoinURI(uri, &rv));
    QVERIFY(rv.address == QString("fMafLhSZPSfa6iipsC5hW1tuZJYYVDNZa9"));
    QVERIFY(rv.amount == 10000000000LL);
    QVERIFY(rv.label == QString("Wikipedia Example"));

    uri.setUrl(QString("sjwcoin:fMafLhSZPSfa6iipsC5hW1tuZJYYVDNZa9?message=Wikipedia Example Address"));
    QVERIFY(GUIUtil::parseBitcoinURI(uri, &rv));
    QVERIFY(rv.address == QString("fMafLhSZPSfa6iipsC5hW1tuZJYYVDNZa9"));
    QVERIFY(rv.label == QString());

    QVERIFY(GUIUtil::parseBitcoinURI("sjwcoin://fMafLhSZPSfa6iipsC5hW1tuZJYYVDNZa9?message=Wikipedia Example Address", &rv));
    QVERIFY(rv.address == QString("fMafLhSZPSfa6iipsC5hW1tuZJYYVDNZa9"));
    QVERIFY(rv.label == QString());

    uri.setUrl(QString("sjwcoin:fMafLhSZPSfa6iipsC5hW1tuZJYYVDNZa9?req-message=Wikipedia Example Address"));
    QVERIFY(GUIUtil::parseBitcoinURI(uri, &rv));

    uri.setUrl(QString("sjwcoin:fMafLhSZPSfa6iipsC5hW1tuZJYYVDNZa9?amount=1,000&label=Wikipedia Example"));
    QVERIFY(!GUIUtil::parseBitcoinURI(uri, &rv));

    uri.setUrl(QString("sjwcoin:fMafLhSZPSfa6iipsC5hW1tuZJYYVDNZa9?amount=1,000.0&label=Wikipedia Example"));
    QVERIFY(!GUIUtil::parseBitcoinURI(uri, &rv));
}
