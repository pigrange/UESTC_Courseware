package com.pigrange.phonebook.app;

import android.app.Application;
import android.database.sqlite.SQLiteDatabase;

import com.pigrange.greendaotest.model.greenDao.DaoMaster;
import com.pigrange.greendaotest.model.greenDao.DaoSession;
import com.pigrange.phonebook.list.MyList;
import com.pigrange.phonebook.list.MyListImpl;
import com.pigrange.phonebook.model.Contacts;

import java.util.List;


public class App extends Application {
    private static DaoSession mDaoSession;
    private static MyList<Contacts> mContactsList;

    @Override
    public void onCreate() {
        super.onCreate();
        init();
    }

    private void init() {
        DaoMaster.DevOpenHelper helper = new DaoMaster.DevOpenHelper(this, "test.db");
        SQLiteDatabase db = helper.getWritableDatabase();
        DaoMaster master = new DaoMaster(db);
        mDaoSession = master.newSession();
        List<Contacts> contactsList = mDaoSession.getContactsDao().queryBuilder().list();
        mContactsList = new MyListImpl<>();
        for (Contacts contacts : contactsList) {
            mContactsList.add(contacts);
        }
    }

    public static DaoSession getDaoSession() {
        return mDaoSession;
    }

    public static MyList<Contacts> getContactsList() {
        if (mContactsList != null) {
            return mContactsList;
        } else {
            return new MyListImpl<>();
        }
    }
}
