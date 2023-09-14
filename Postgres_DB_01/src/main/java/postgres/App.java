package postgres;

import postgres.models.User;
import postgres.workingClass.DataBaseWorking;


public class App {
    public static void main(String[] args) throws Exception{
        DataBaseWorking dataBaseWorking = new DataBaseWorking();
        User user = dataBaseWorking.select_user("user_1");
        System.out.println(user);

        String insert = dataBaseWorking.insert_user(new User("user_8", "77777", "2023-09-08", "user_7@mail.ru"));
        System.out.println(insert);

    }
}