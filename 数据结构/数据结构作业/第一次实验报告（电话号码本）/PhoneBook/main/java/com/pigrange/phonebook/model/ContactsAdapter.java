package com.pigrange.phonebook.model;

import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.renderscript.ScriptIntrinsicYuvToRGB;
import android.support.annotation.NonNull;
import android.support.constraint.ConstraintLayout;
import android.support.v7.widget.PopupMenu;
import android.support.v7.widget.RecyclerView;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.MenuInflater;
import android.view.MenuItem;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.TextView;

import com.mcxtzhang.swipemenulib.SwipeMenuLayout;
import com.pigrange.phonebook.activity.CreateContacts;
import com.pigrange.phonebook.activity.MainActivity;
import com.pigrange.phonebook.app.App;
import com.pigrange.phonebook.R;
import com.pigrange.phonebook.activity.ShowContacts;
import com.pigrange.phonebook.list.MyList;


import static android.support.constraint.Constraints.TAG;
import static com.pigrange.phonebook.activity.MainActivity.ADDRESS;
import static com.pigrange.phonebook.activity.MainActivity.EXTRA_1;
import static com.pigrange.phonebook.activity.MainActivity.EXTRA_2;
import static com.pigrange.phonebook.activity.MainActivity.NAME;
import static com.pigrange.phonebook.activity.MainActivity.NUMBER;
import static com.pigrange.phonebook.activity.MainActivity.REQUEST_CODE;

public class ContactsAdapter extends RecyclerView.Adapter<ContactsAdapter.ViewHolder> {
    private MyList<Contacts> mContactsList;
    private int resId;
    private Activity mContext;

    public ContactsAdapter(MyList<Contacts> myList, int resId) {
        this.mContactsList = myList;
        this.resId = resId;
    }

    @NonNull
    @Override
    public ViewHolder onCreateViewHolder(@NonNull ViewGroup parent, int viewType) {
        mContext = (Activity) parent.getContext();
        View v = LayoutInflater.from(mContext).inflate(resId, parent, false);
        return new ViewHolder(v);
    }

    @Override
    public void onBindViewHolder(@NonNull ViewHolder holder, int position) {
        final Contacts contacts = mContactsList.get(position);

        holder.item.setOnClickListener((view) -> {
            Intent intent = new Intent(mContext, ShowContacts.class);
            intent.putExtra(NAME, contacts.getName());
            intent.putExtra(NUMBER, contacts.getValue());
            intent.putExtra(ADDRESS, contacts.getAddress());
            intent.putExtra(EXTRA_1, contacts.getExtraNumber1());
            intent.putExtra(EXTRA_2, contacts.getExtraNumber2());
            mContext.startActivity(intent);
        });

        holder.item.setOnLongClickListener(v -> {
            PopupMenu popupMenu = new PopupMenu(mContext, v);
            popupMenu.getMenuInflater().inflate(R.menu.popu_menu, popupMenu.getMenu());
            popupMenu.show();

            popupMenu.setOnMenuItemClickListener(item -> {
                Intent intent = new Intent(mContext, CreateContacts.class);
                intent.putExtra(MainActivity.Key, contacts.getPhoneNumber());
                intent.putExtra(CreateContacts.MODE, CreateContacts.MODE_EDIT);
                mContext.startActivityForResult(intent, REQUEST_CODE);
                return true;
            });
            return true;
        });

        holder.delete.setOnClickListener((v) -> {
            App.getDaoSession().getContactsDao().delete(contacts);
            mContactsList.remove(position);
            holder.mSwipeMenuLayout.quickClose();
            notifyDataSetChanged();
        });
        Log.e(TAG, "onBindViewHolder: " + position);
        holder.tv_name.setText(contacts.getName());
    }

    @Override
    public int getItemCount() {
        return mContactsList.size();
    }

    static class ViewHolder extends RecyclerView.ViewHolder {
        private ConstraintLayout item;
        private TextView tv_name;
        private SwipeMenuLayout mSwipeMenuLayout;
        private Button delete;

        ViewHolder(View itemView) {
            super(itemView);
            item = itemView.findViewById(R.id.item_main);
            tv_name = itemView.findViewById(R.id.item_contacts_name);
            mSwipeMenuLayout = itemView.findViewById(R.id.item_contacts_swiper);
            delete = itemView.findViewById(R.id.item_contacts_button_delete);
        }
    }

}
