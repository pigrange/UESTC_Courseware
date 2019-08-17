package com.pigrange.phonebook.activity;

import android.content.Intent;
import android.os.Bundle;
import android.support.v7.app.ActionBar;
import android.support.v7.app.AppCompatActivity;
import android.support.v7.widget.Toolbar;
import android.view.Menu;
import android.view.MenuItem;
import android.widget.EditText;
import android.widget.Toast;

import com.pigrange.phonebook.R;
import com.pigrange.phonebook.app.App;
import com.pigrange.phonebook.list.MyList;
import com.pigrange.phonebook.model.Contacts;

public class CreateContacts extends AppCompatActivity {
    public static final String MODE = "MODE";
    public static final String MODE_CREATE = "CREATE";
    public static final String MODE_EDIT = "EDIT";
    private long key = -1;

    private String currentMode;

    private EditText tv_name;
    private EditText tv_number;
    private EditText tv_address;

    private EditText tv_extraNumber1;
    private EditText tv_extraNumber2;

    private MyList<Contacts> contactsList;
    private Contacts contacts;


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_create_contacts);

        init();
    }

    private void init() {
        contactsList = App.getContactsList();
        tv_name = findViewById(R.id.create_contacts_name);
        tv_number = findViewById(R.id.create_contacts_number);
        tv_address = findViewById(R.id.create_contacts_address);

        tv_extraNumber1 = findViewById(R.id.create_contacts_extra_number1);
        tv_extraNumber2 = findViewById(R.id.create_contacts_extra_number2);

        Toolbar toolbar = findViewById(R.id.mtoolBar);
        setSupportActionBar(toolbar);
        ActionBar actionBar = getSupportActionBar();
        if (actionBar != null) {
            actionBar.setDisplayHomeAsUpEnabled(true);
        }

        Intent request = getIntent();

        if (request.getStringExtra(MODE).equals(MODE_CREATE)) {
            currentMode = MODE_CREATE;
            long num = request.getLongExtra(MainActivity.NUMBER, -1);
            String name = request.getStringExtra(MainActivity.NAME);
            if (num != -1) {
                tv_number.setText(String.valueOf(num));
            }
            tv_name.setText(name);
        }
        if (request.getStringExtra(MODE).equals(MODE_EDIT)) {
            currentMode = MODE_EDIT;
            key = request.getLongExtra(MainActivity.Key, -1);
            if (actionBar != null) {
                actionBar.setTitle("修改联系人");
            }
            loadContacts();
        }
    }

    private void loadContacts() {
        contacts = contactsList.getByValue(key);

        String name = contacts.getName();
        String address = contacts.getAddress();
        long number = contacts.getPhoneNumber();
        long extra_num1 = contacts.getExtraNumber1();
        long extra_num2 = contacts.getExtraNumber2();

        tv_name.setText(name);
        tv_address.setText(address);
        tv_number.setText(String.valueOf(number));

        if (extra_num1 == -1) {
            tv_extraNumber1.setText(String.valueOf(""));
        } else {
            tv_extraNumber1.setText(String.valueOf(extra_num1));
        }

        if (extra_num2 == -1) {
            tv_extraNumber2.setText(String.valueOf(""));
        } else {
            tv_extraNumber2.setText(String.valueOf(extra_num2));
        }
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        switch (item.getItemId()) {
            case android.R.id.home:
                finish();
                break;
            case R.id.bt_create:
                checkContacts();
        }
        return super.onOptionsItemSelected(item);
    }

    private void checkContacts() {
        if (currentMode.equals(MODE_CREATE)) {
            contacts = new Contacts();
        }
        if (tv_name.getText().toString().equals("")) {
            showToast("姓名为空！");
        } else if (tv_address.getText().toString().equals("")) {
            showToast("地址为空！");
        } else if (tv_number.getText().toString().equals("")) {
            showToast("电话为空！");
        } else if (tv_number.getText().toString().length() != 11 || Long.valueOf(tv_number.getText().toString()) < 0) {
            showToast("请输入正确格式的电话号码");
        } else {

            if (currentMode.equals(MODE_EDIT)) {
                if (ifHasSameName(tv_name.getText().toString(), key) &&
                        ifHasSameNumber(Long.valueOf(tv_number.getText().toString()), contacts.getName())) {
                    createContacts();
                    finish();
                } else {
                    showToast("姓名或电话号码重复");
                    tv_number.setText("");
                    tv_name.setText("");
                }

            } else {
                if (ifHasSameName(tv_name.getText().toString(), -1) &&
                        ifHasSameNumber(Long.valueOf(tv_number.getText().toString()), "...")) {
                    createContacts();
                    contactsList.add(0, contacts);
                    finish();
                } else {
                    showToast("姓名或电话号码重复");
                    tv_number.setText("");
                    tv_name.setText("");
                }

            }
        }
    }

    private void createContacts() {
        if (tv_extraNumber1.getText().toString().equals("")) {
            contacts.setExtraNumber1(-1);
        } else {
            long number_extra1 = Long.valueOf(tv_extraNumber1.getText().toString());
            contacts.setExtraNumber1(number_extra1);
        }
        if (tv_extraNumber2.getText().toString().equals("")) {
            contacts.setExtraNumber2(-1);
        } else {
            long number_extra2 = Long.valueOf(tv_extraNumber2.getText().toString());
            contacts.setExtraNumber2(number_extra2);
        }
        long number = Long.valueOf(tv_number.getText().toString());
        contacts.setAddress(tv_address.getText().toString());
        contacts.setName(tv_name.getText().toString());
        contacts.setPhoneNumber(number);
        App.getDaoSession().getContactsDao().insertOrReplace(contacts);
        Intent intent = new Intent();
        setResult(RESULT_OK, intent);
    }

    private void showToast(String s) {
        Toast.makeText(this, s, Toast.LENGTH_SHORT).show();
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        getMenuInflater().inflate(R.menu.menu_create, menu);
        return true;
    }

    private boolean ifHasSameName(String name, long key) {
        for (int i = 0; i < contactsList.size(); i++) {
            Contacts contacts = contactsList.get(i);
            if (contacts.getName().equals(name)) {
                return (key == contacts.getPhoneNumber());
            }
        }
        return true;
    }

    private boolean ifHasSameNumber(long number, String name) {
        for (int i = 0; i < contactsList.size(); i++) {
            Contacts contacts = contactsList.get(i);
            if (contacts.getPhoneNumber() == number) {
                return (name.equals(contacts.getName()));
            }
        }
        return true;
    }
}
