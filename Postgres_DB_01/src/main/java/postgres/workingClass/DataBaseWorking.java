package postgres.workingClass;

import postgres.models.User;

import java.sql.*;

public class DataBaseWorking {
    private static final String url = "jdbc:postgresql://localhost:54321/db1";
    private static final String dataBaseUser = "postgres";
    private static final String dataBasePassword = "postgres";
    private static final String table1 = "public.users";
    private static final String table2 = "public.email";


    public User select_user(String login) throws Exception {
        User user = null;
        String query = "SELECT * FROM " + table1 + " JOIN " + table2 + " USING (login) WHERE login = '" + login + "'";
        Connection con = null;
        try {
            con = DriverManager.getConnection(url, dataBaseUser, dataBasePassword);
            Statement statement = con.createStatement();
            ResultSet resultSet = statement.executeQuery(query);
            if(resultSet.next()){
                user = new User(resultSet.getString("login"), resultSet.getString("password"), resultSet.getString("date"), resultSet.getString("email"));
            }

            return user;
        } catch (SQLException e) {
            System.out.println(e.getMessage());
        } finally {
            if (con != null) {
                con.close();
            }

        }
        return null;
    }

    public String insert_user(User user) {
        String query = " INSERT INTO " + table1 + "( login, password, date ) values ( ?, ?, ? ); \n" + " INSERT INTO " + table2 + "( login, email ) values ( ?, ? );";
        try (Connection con = DriverManager.getConnection(url, dataBaseUser, dataBasePassword);
             PreparedStatement preparedStatement = con.prepareStatement(query)) {

            preparedStatement.setString(1, user.getLogin());
            preparedStatement.setString(2, user.getPassword());
            preparedStatement.setString(3, user.getDate());
            preparedStatement.setString(4, user.getLogin());
            preparedStatement.setString(5, user.getEmail());

            int entry_Update = preparedStatement.executeUpdate();
            return new String("Updated rows = " + entry_Update);

        } catch (SQLException e) {
            System.out.println(e.getMessage());
        }
        return null;
    }
}














//                preparedStatement.setString(3, Date.valueof(date.format(formatter)));