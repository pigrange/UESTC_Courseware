package com.pigrange.phonebook.activity;

import android.Manifest;
import android.content.Intent;
import android.content.pm.PackageManager;
import android.os.Bundle;
import android.support.design.widget.FloatingActionButton;
import android.support.v4.app.ActivityCompat;
import android.support.v4.content.ContextCompat;
import android.support.v7.app.AlertDialog;
import android.support.v7.app.AppCompatActivity;
import android.support.v7.widget.DividerItemDecoration;
import android.support.v7.widget.LinearLayoutManager;
import android.support.v7.widget.RecyclerView;
import android.support.v7.widget.Toolbar;
import android.text.InputType;
import android.view.Menu;
import android.view.MenuItem;
import android.widget.EditText;

import com.pigrange.phonebook.R;
import com.pigrange.phonebook.app.App;
import com.pigrange.phonebook.list.MyList;
import com.pigrange.phonebook.model.Contacts;
import com.pigrange.phonebook.model.ContactsAdapter;


public class MainActivity extends AppCompatActivity {
    public static final int REQUEST_CODE = 111;
    public static final String NAME = "name";
    public static final String NUMBER = "number";
    public static final String ADDRESS = "address";
    public static final String EXTRA_1 = "extra1";
    public static final String EXTRA_2 = "extra2";
    public static final String Key = "key";

    private static final int MODE_SEARCH_BY_NUMBER = 33281;
    private static final int MODE_SEARCH_BY_NAME = 26624;

    private MyList<Contacts> mContactsList;
    private ContactsAdapter adapter;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        checkPermissions();
        init();
    }


    private void init() {
        FloatingActionButton floatingActionButton = findViewById(R.id.button_floating_main);
        RecyclerView recyclerView = findViewById(R.id.list_main);
        Toolbar toolbar = findViewById(R.id.mtoolBar);
        setSupportActionBar(toolbar);

        mContactsList = App.getContactsList();
        adapter = new ContactsAdapter(mContactsList, R.layout.item_contacts);

        RecyclerView.LayoutManager manager = new LinearLayoutManager(this);
        recyclerView.setLayoutManager(manager);
        recyclerView.setAdapter(adapter);
        recyclerView.addItemDecoration(new DividerItemDecoration(this, DividerItemDecoration.VERTICAL));

        floatingActionButton.setOnClickListener(v -> {
            Intent intent = new Intent(MainActivity.this, CreateContacts.class);
            intent.putExtra(CreateContacts.MODE, CreateContacts.MODE_CREATE);
            startActivityForResult(intent, REQUEST_CODE);
        });
    }

    private void checkPermissions() {
        if (ContextCompat.checkSelfPermission(this, Manifest.permission.WRITE_EXTERNAL_STORAGE) != PackageManager.PERMISSION_GRANTED &&
                ContextCompat.checkSelfPermission(this, Manifest.permission.READ_EXTERNAL_STORAGE) != PackageManager.PERMISSION_GRANTED) {
            ActivityCompat.requestPermissions(this, new String[]{Manifest.permission.READ_EXTERNAL_STORAGE, Manifest.permission.WRITE_EXTERNAL_STORAGE}, 1);
        }
    }

    private void showSearchDialog(String title, int mode) {
        final EditText editText = new EditText(MainActivity.this);

        if (mode == MODE_SEARCH_BY_NUMBER) {
            editText.setInputType(InputType.TYPE_CLASS_NUMBER);
        }

        AlertDialog.Builder inputDialog =
                new AlertDialog.Builder(MainActivity.this);
        inputDialog.setTitle(title).setView(editText);
        inputDialog.setPositiveButton("确定", (dialog, which) -> {

            if (mode == MODE_SEARCH_BY_NUMBER) {
                long number = Long.valueOf(editText.getText().toString());
                int pos = mContactsList.searchByValue(number);
                if (pos != -1) {
                    Contacts contacts = mContactsList.get(pos);
                    showContacts(contacts);
                } else {
                    showCreateDialog("", number);
                }
            }

            if (mode == MODE_SEARCH_BY_NAME) {
                String name = editText.getText().toString();
                int pos = searchByName(name);
                if (pos != -1) {
                    Contacts contacts = mContactsList.get(pos);
                    showContacts(contacts);
                } else {
                    showCreateDialog(name, -1L);
                }
            }
        });

        inputDialog.setNegativeButton("取消", (dialog, which) -> dialog.dismiss());
        inputDialog.show();
    }


    private void showCreateDialog(String name, Long number) {
        final AlertDialog.Builder normalDialog =
                new AlertDialog.Builder(MainActivity.this);
        normalDialog.setTitle("提示");
        normalDialog.setMessage("未查找到联系人,是否新建");
        normalDialog.setPositiveButton("确定",
                (dialog, which) -> {
                    Intent intent = new Intent(MainActivity.this, CreateContacts.class);
                    intent.putExtra(NUMBER, number);
                    intent.putExtra(NAME, name);
                    intent.putExtra(CreateContacts.MODE, CreateContacts.MODE_CREATE);
                    startActivityForResult(intent, REQUEST_CODE);
                });
        normalDialog.setNegativeButton("关闭",
                (dialog, which) -> dialog.dismiss());
        normalDialog.show();
    }

    private int searchByName(String name) {
        for (int i = 0; i < mContactsList.size(); i++) {
            if (mContactsList.get(i).getName().equals(name)) {
                return i;
            }
        }
        return -1;
    }

    private void showContacts(Contacts contacts) {
        Intent intent = new Intent(MainActivity.this, ShowContacts.class);
        intent.putExtra(NAME, contacts.getName());
        intent.putExtra(NUMBER, contacts.getValue());
        intent.putExtra(ADDRESS, contacts.getAddress());
        intent.putExtra(EXTRA_1, contacts.getExtraNumber1());
        intent.putExtra(EXTRA_2, contacts.getExtraNumber2());
        startActivity(intent);
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        getMenuInflater().inflate(R.menu.menu, menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        switch (item.getItemId()) {
            case R.id.sort:
                mContactsList.sortByValue();
                adapter.notifyDataSetChanged();
                break;
            case R.id.search:
                showSearchDialog("请输入电话号码", MODE_SEARCH_BY_NUMBER);
                break;
            case R.id.search_by_name:
                showSearchDialog("请输入姓名", MODE_SEARCH_BY_NAME);
            default:
                break;
        }
        return true;
    }

    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
        super.onActivityResult(requestCode, resultCode, data);
        if (requestCode == REQUEST_CODE && resultCode == RESULT_OK) {
            adapter.notifyDataSetChanged();
        }
    }
}
