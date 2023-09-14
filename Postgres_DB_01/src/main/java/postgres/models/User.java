package postgres.models;

import java.time.LocalDate;

public class User {
    private String login;
    private String password;
    private String date;
    private String email;

    @Override
    public String toString() {
        return "User{" +
                "login='" + login + '\'' +
                ", password='" + password + '\'' +
                ", date='" + date + '\'' +
                ", email='" + email + '\'' +
                '}';
    }

    public User(String login, String password, String email){
        this.login = login;
        this.password = password;
        this.email = email;
        this.date = LocalDate.now().toString();
    }

    public User(String login, String password, String date, String email){
        this.login = login;
        this.password = password;
        this.email = email;
        this.date = date;
    }

    public void setLogin(String login) {
        this.login = login;
    }

    public void setPassword(String password) {
        this.password = password;
    }

       public void setDate(String date) {
        this.date = LocalDate.now().toString();
    }

    public void setEmail(String email) {
        this.email = email;
    }

    public String getLogin() {
        return login;
    }

    public String getPassword() {
        return password;
    }

    public String getEmail() {
        return email;
    }

    public String getDate() {
        return date;
    }

}
