#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ctime>
#include <memory>
#include <map>
#include <iomanip>
#include <cstdlib>

#include <windows.h> // 仅适用于 Windows
using namespace std;

// 日期类
class Date {
private:
    int year;
    int month;
    int day;

public:
    Date() : year(0), month(0), day(0) {}
    Date(int y, int m, int d) : year(y), month(m), day(d) {}

    // 从系统获取当前日期
    static Date getCurrentDate() {
        time_t now = time(0);
        tm* ltm = localtime(&now);
        return Date(1900 + ltm->tm_year, 1 + ltm->tm_mon, ltm->tm_mday);
    }

    // 从字符串解析日期 (格式: YYYY-MM-DD)
    static Date fromString(const string& dateStr) {
        int y, m, d;
        if (sscanf(dateStr.c_str(), "%d-%d-%d", &y, &m, &d) == 3) {
            return Date(y, m, d);
        }
        return Date(); // 返回无效日期
    }

    // 转换为字符串
    string toString() const {
        char buffer[11];
        sprintf(buffer, "%04d-%02d-%02d", year, month, day);
        return string(buffer);
    }

    // 日期比较
    bool operator<(const Date& other) const {
        if (year != other.year) return year < other.year;
        if (month != other.month) return month < other.month;
        return day < other.day;
    }

    bool operator==(const Date& other) const {
        return year == other.year && month == other.month && day == other.day;
    }

    // 检查日期是否有效
    bool isValid() const {
        if (year < 1900 || year > 2100) return false;
        if (month < 1 || month > 12) return false;
        if (day < 1 || day > 31) return false;

        // 检查每月天数
        int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        // 闰年处理
        if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) {
            daysInMonth[1] = 29;
        }
        return day <= daysInMonth[month - 1];
    }

    // 获取日期组件
    int getYear() const { return year; }
    int getMonth() const { return month; }
    int getDay() const { return day; }
};

// 枚举类型
enum Gender { MALE, FEMALE, OTHER };
enum UserRole { MANAGER, EMPLOYEE };

// 文件操作工具类
class FileHelper {
public:
    // 写入文本文件
    static bool writeTextFile(const string& filename, const string& content, bool append = false) {
        ofstream file;
        if (append) {
            file.open(filename, ios::app);
        } else {
            file.open(filename);
        }

        if (!file.is_open()) {
            return false;
        }

        file << content;
        file.close();
        return true;
    }

    // 读取文本文件
    static bool readTextFile(const string& filename, string& content) {
        ifstream file(filename);
        if (!file.is_open()) {
            return false;
        }

        content.assign((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
        file.close();
        return true;
    }

    // 检查文件是否存在
    static bool fileExists(const string& filename) {
        ifstream file(filename);
        return file.good();
    }
};

// 字符串工具类
class StringHelper {
public:
    // 分割字符串
    static vector<string> split(const string& str, char delimiter) {
        vector<string> tokens;
        string token;
        size_t start = 0, end = 0;

        while ((end = str.find(delimiter, start)) != string::npos) {
            token = str.substr(start, end - start);
            tokens.push_back(token);
            start = end + 1;
        }

        tokens.push_back(str.substr(start));
        return tokens;
    }

    // 去除字符串首尾空格
    static string trim(const string& str) {
        size_t first = str.find_first_not_of(" \t\n\r");
        if (first == string::npos)
            return "";

        size_t last = str.find_last_not_of(" \t\n\r");
        return str.substr(first, last - first + 1);
    }

    // 转换为大写
    static string toUpper(const string& str) {
        string result = str;
        for (char& c : result) {
            c = toupper(c);
        }
        return result;
    }
};


// 用户类
class User {
private:
    string username;
    string password;
    UserRole role;

public:
    User(const string& username, const string& password, UserRole role)
            : username(username), password(password), role(role) {}

    // 获取用户信息
    string getUsername() const { return username; }
    UserRole getRole() const { return role; }

    // 验证密码
    bool verifyPassword(const string& inputPassword) const {
        return password == inputPassword;
    }
};

// 用户管理类
class UserManager {
private:
    vector<User> users;
    User* currentUser = nullptr;

public:
    // 添加用户
    void addUser(const string& username, const string& password, UserRole role) {
        users.emplace_back(username, password, role);
    }

    // 用户登录
    bool login(const string& username, const string& password) {
        for (auto& user : users) {
            if (user.getUsername() == username && user.verifyPassword(password)) {
                currentUser = &user;
                return true;
            }
        }
        return false;
    }

    // 用户登出
    void logout() {
        currentUser = nullptr;
    }

    // 检查用户是否已登录
    bool isLoggedIn() const {
        return currentUser != nullptr;
    }

    // 获取当前用户角色
    UserRole getCurrentUserRole() const {
        if (currentUser) {
            return currentUser->getRole();
        }
        return MANAGER; // 默认返回管理员角色
    }

    // 初始化默认用户
    void initializeDefaultUsers() {
        // 添加默认管理员用户
        addUser("admin", "admin123", MANAGER);
    }
};

// 员工类
class Employee {
private:
    int id;
    string name;
    string idCard;
    Gender gender;
    Date birthDate;
    string hometown;
    string ethnicity;
    string college;
    string className;
    string address;
    string phone;
    int hourlyWage;
    string username;
    string password;
    string notes;

public:
    Employee(int id, const string& name, const string& idCard, Gender gender, const Date& birthDate,
             const string& hometown, const string& ethnicity, const string& college, const string& className,
             const string& address, const string& phone, int hourlyWage,
             const string& username, const string& password, const string& notes)
            : id(id), name(name), idCard(idCard), gender(gender), birthDate(birthDate),
              hometown(hometown), ethnicity(ethnicity), college(college), className(className),
              address(address), phone(phone), hourlyWage(hourlyWage),
              username(username), password(password), notes(notes) {}

    // 获取员工信息
    int getId() const { return id; }
    string getName() const { return name; }
    string getIdCard() const { return idCard; }
    Gender getGender() const { return gender; }
    Date getBirthDate() const { return birthDate; }
    string getHometown() const { return hometown; }
    string getEthnicity() const { return ethnicity; }
    string getCollege() const { return college; }
    string getClassName() const { return className; }
    string getAddress() const { return address; }
    string getPhone() const { return phone; }
    int getHourlyWage() const { return hourlyWage; }
    string getUsername() const { return username; }
    string getPassword() const { return password; }
    string getNotes() const { return notes; }

    // 设置员工信息
    void setName(const string& name) { this->name = name; }
    void setIdCard(const string& idCard) { this->idCard = idCard; }
    void setGender(Gender gender) { this->gender = gender; }
    void setBirthDate(const Date& birthDate) { this->birthDate = birthDate; }
    void setHometown(const string& hometown) { this->hometown = hometown; }
    void setEthnicity(const string& ethnicity) { this->ethnicity = ethnicity; }
    void setCollege(const string& college) { this->college = college; }
    void setClassName(const string& className) { this->className = className; }
    void setAddress(const string& address) { this->address = address; }
    void setPhone(const string& phone) { this->phone = phone; }
    void setHourlyWage(int hourlyWage) { this->hourlyWage = hourlyWage; }
    void setUsername(const string& username) { this->username = username; }
    void setPassword(const string& password) { this->password = password; }
    void setNotes(const string& notes) { this->notes = notes; }

    // 转换为CSV格式字符串
    string toCsvString() const {
        string genderStr = (gender == MALE) ? "MALE" : (gender == FEMALE) ? "FEMALE" : "OTHER";

        return to_string(id) + "," +
               name + "," +
               idCard + "," +
               genderStr + "," +
               birthDate.toString() + "," +
               hometown + "," +
               ethnicity + "," +
               college + "," +
               className + "," +
               address + "," +
               phone + "," +
               to_string(hourlyWage) + "," +
               username + "," +
               password + "," +
               notes;
    }

    // 从CSV格式字符串创建员工对象
    static Employee fromCsvString(const string& csvString) {
        vector<string> tokens = StringHelper::split(csvString, ',');

        if (tokens.size() < 15) {
            // 返回一个默认构造的员工对象
            return Employee(0, "", "", MALE, Date(), "", "", "", "", "", "", 0, "", "", "");
        }

        // 解析性别
        Gender gender = MALE;
        if (tokens[3] == "FEMALE") gender = FEMALE;
        else if (tokens[3] == "OTHER") gender = OTHER;

        return Employee(
                stoi(tokens[0]),           // ID
                tokens[1],                 // 姓名
                tokens[2],                 // 身份证号
                gender,                    // 性别
                Date::fromString(tokens[4]), // 出生日期
                tokens[5],                 // 籍贯
                tokens[6],                 // 民族
                tokens[7],                 // 学院
                tokens[8],                 // 班级
                tokens[9],                 // 地址
                tokens[10],                // 电话
                stoi(tokens[11]),          // 小时工资
                tokens[12],                // 用户名
                tokens[13],                // 密码
                tokens[14]                 // 备注
        );
    }
};

// 员工管理类
class EmployeeManager {
private:
    vector<Employee> employees;
    const string filename = "employee.txt";

    // 加载员工数据
    void loadEmployees() {
        employees.clear();

        if (!FileHelper::fileExists(filename)) {
            return;
        }

        string content;
        if (!FileHelper::readTextFile(filename, content)) {
            return;
        }

        vector<string> lines = StringHelper::split(content, '\n');
        for (const auto& line : lines) {
            if (!line.empty()) {
                employees.push_back(Employee::fromCsvString(line));
            }
        }
    }

    // 保存员工数据
    void saveEmployees() const {
        string content;
        for (const auto& employee : employees) {
            content += employee.toCsvString() + "\n";
        }

        FileHelper::writeTextFile(filename, content);
    }

public:
    EmployeeManager() {
        loadEmployees();
    }

    // 添加员工
    bool addEmployee(const Employee& employee) {
        // 检查身份证号是否已存在
        for (const auto& emp : employees) {
            if (emp.getIdCard() == employee.getIdCard()) {
                return false; // 身份证号重复
            }
        }

        employees.push_back(employee);
        saveEmployees();
        return true;
    }

    // 修改员工信息
    bool updateEmployee(int id, const Employee& updatedEmployee) {
        for (auto& emp : employees) {
            if (emp.getId() == id) {
                // 检查新身份证号是否与其他员工重复
                if (emp.getIdCard() != updatedEmployee.getIdCard()) {
                    for (const auto& otherEmp : employees) {
                        if (otherEmp.getId() != id && otherEmp.getIdCard() == updatedEmployee.getIdCard()) {
                            return false; // 身份证号重复
                        }
                    }
                }

                emp = updatedEmployee;
                saveEmployees();
                return true;
            }
        }
        return false; // 未找到该员工
    }

    // 删除员工
    bool deleteEmployee(int id) {
        for (auto it = employees.begin(); it != employees.end(); ++it) {
            if (it->getId() == id) {
                employees.erase(it);
                saveEmployees();
                return true;
            }
        }
        return false; // 未找到该员工
    }

    // 查找员工
    Employee* findEmployeeById(int id) {
        for (auto& emp : employees) {
            if (emp.getId() == id) {
                return &emp;
            }
        }
        return nullptr;
    }

    // 查找员工
    Employee* findEmployeeByIdCard(const string& idCard) {
        for (auto& emp : employees) {
            if (emp.getIdCard() == idCard) {
                return &emp;
            }
        }
        return nullptr;
    }

    // 获取所有员工
    const vector<Employee>& getAllEmployees() const {
        return employees;
    }

    // 获取下一个可用的员工ID
    int getNextEmployeeId() const {
        if (employees.empty()) {
            return 1;
        }

        int maxId = 0;
        for (const auto& emp : employees) {
            if (emp.getId() > maxId) {
                maxId = emp.getId();
            }
        }

        return maxId + 1;
    }
};


// 供应商类
class Supplier {
private:
    int id;
    string name;
    string phone;
    string address;
    string notes;

public:
    Supplier(int id, const string& name, const string& phone, const string& address, const string& notes)
            : id(id), name(name), phone(phone), address(address), notes(notes) {}

    // 获取供应商信息
    int getId() const { return id; }
    string getName() const { return name; }
    string getPhone() const { return phone; }
    string getAddress() const { return address; }
    string getNotes() const { return notes; }

    // 设置供应商信息
    void setName(const string& name) { this->name = name; }
    void setPhone(const string& phone) { this->phone = phone; }
    void setAddress(const string& address) { this->address = address; }
    void setNotes(const string& notes) { this->notes = notes; }

    // 转换为CSV格式字符串
    string toCsvString() const {
        return to_string(id) + "," +
               name + "," +
               phone + "," +
               address + "," +
               notes;
    }

    // 从CSV格式字符串创建供应商对象
    static Supplier fromCsvString(const string& csvString) {
        vector<string> tokens = StringHelper::split(csvString, ',');

        if (tokens.size() < 5) {
            return Supplier(0, "", "", "", "");
        }

        return Supplier(
                stoi(tokens[0]),     // ID
                tokens[1],           // 名称
                tokens[2],           // 电话
                tokens[3],           // 地址
                tokens[4]            // 备注
        );
    }
};

// 供应商管理类
class SupplierManager {
private:
    vector<Supplier> suppliers;
    const string filename = "supplier.txt";

    // 加载供应商数据
    void loadSuppliers() {
        suppliers.clear();

        if (!FileHelper::fileExists(filename)) {
            return;
        }

        string content;
        if (!FileHelper::readTextFile(filename, content)) {
            return;
        }

        vector<string> lines = StringHelper::split(content, '\n');
        for (const auto& line : lines) {
            if (!line.empty()) {
                suppliers.push_back(Supplier::fromCsvString(line));
            }
        }
    }

    // 保存供应商数据
    void saveSuppliers() const {
        string content;
        for (const auto& supplier : suppliers) {
            content += supplier.toCsvString() + "\n";
        }

        FileHelper::writeTextFile(filename, content);
    }

public:
    SupplierManager() {
        loadSuppliers();
    }

    // 添加供应商
    bool addSupplier(const Supplier& supplier) {
        // 检查供应商ID是否已存在
        for (const auto& sup : suppliers) {
            if (sup.getId() == supplier.getId()) {
                return false; // 供应商ID重复
            }
        }

        suppliers.push_back(supplier);
        saveSuppliers();
        return true;
    }

    // 修改供应商信息
    bool updateSupplier(int id, const Supplier& updatedSupplier) {
        for (auto& sup : suppliers) {
            if (sup.getId() == id) {
                sup = updatedSupplier;
                saveSuppliers();
                return true;
            }
        }
        return false; // 未找到该供应商
    }

    // 删除供应商
    bool deleteSupplier(int id) {
        for (auto it = suppliers.begin(); it != suppliers.end(); ++it) {
            if (it->getId() == id) {
                suppliers.erase(it);
                saveSuppliers();
                return true;
            }
        }
        return false; // 未找到该供应商
    }

    // 查找供应商
    Supplier* findSupplierById(int id) {
        for (auto& sup : suppliers) {
            if (sup.getId() == id) {
                return &sup;
            }
        }
        return nullptr;
    }

    // 获取所有供应商
    const vector<Supplier>& getAllSuppliers() const {
        return suppliers;
    }

    // 获取下一个可用的供应商ID
    int getNextSupplierId() const {
        if (suppliers.empty()) {
            return 1;
        }

        int maxId = 0;
        for (const auto& sup : suppliers) {
            if (sup.getId() > maxId) {
                maxId = sup.getId();
            }
        }

        return maxId + 1;
    }
};

// 商品类
class Goods {
private:
    int id;
    string name;
    int supplierId;

public:
    Goods(int id, const string& name, int supplierId)
            : id(id), name(name), supplierId(supplierId) {}

    // 获取商品信息
    int getId() const { return id; }
    string getName() const { return name; }
    int getSupplierId() const { return supplierId; }

    // 设置商品信息
    void setName(const string& name) { this->name = name; }
    void setSupplierId(int supplierId) { this->supplierId = supplierId; }

    // 转换为CSV格式字符串
    string toCsvString() const {
        return to_string(id) + "," +
               name + "," +
               to_string(supplierId);
    }

    // 从CSV格式字符串创建商品对象
    static Goods fromCsvString(const string& csvString) {
        vector<string> tokens = StringHelper::split(csvString, ',');

        if (tokens.size() < 3) {
            return Goods(0, "", 0);
        }

        return Goods(
                stoi(tokens[0]),     // ID
                tokens[1],           // 名称
                stoi(tokens[2])      // 供应商ID
        );
    }
};

// 商品管理类
class GoodsManager {
private:
    vector<Goods> goodsList;
    const string filename = "goodsinfo.txt";

    // 加载商品数据
    void loadGoods() {
        goodsList.clear();

        if (!FileHelper::fileExists(filename)) {
            return;
        }

        string content;
        if (!FileHelper::readTextFile(filename, content)) {
            return;
        }

        vector<string> lines = StringHelper::split(content, '\n');
        for (const auto& line : lines) {
            if (!line.empty()) {
                goodsList.push_back(Goods::fromCsvString(line));
            }
        }
    }

    // 保存商品数据
    void saveGoods() const {
        string content;
        for (const auto& goods : goodsList) {
            content += goods.toCsvString() + "\n";
        }

        FileHelper::writeTextFile(filename, content);
    }

public:
    GoodsManager() {
        loadGoods();
    }

    // 添加商品
    bool addGoods(const Goods& goods) {
        // 检查商品ID是否已存在
        for (const auto& g : goodsList) {
            if (g.getId() == goods.getId()) {
                return false; // 商品ID重复
            }
        }

        goodsList.push_back(goods);
        saveGoods();
        return true;
    }

    // 修改商品信息
    bool updateGoods(int id, const Goods& updatedGoods) {
        for (auto& g : goodsList) {
            if (g.getId() == id) {
                g = updatedGoods;
                saveGoods();
                return true;
            }
        }
        return false; // 未找到该商品
    }

    // 删除商品
    bool deleteGoods(int id) {
        for (auto it = goodsList.begin(); it != goodsList.end(); ++it) {
            if (it->getId() == id) {
                goodsList.erase(it);
                saveGoods();
                return true;
            }
        }
        return false; // 未找到该商品
    }

    // 查找商品
    Goods* findGoodsById(int id) {
        for (auto& g : goodsList) {
            if (g.getId() == id) {
                return &g;
            }
        }
        return nullptr;
    }

    // 获取所有商品
    const vector<Goods>& getAllGoods() const {
        return goodsList;
    }

    // 获取下一个可用的商品ID
    int getNextGoodsId() const {
        if (goodsList.empty()) {
            return 1;
        }

        int maxId = 0;
        for (const auto& g : goodsList) {
            if (g.getId() > maxId) {
                maxId = g.getId();
            }
        }

        return maxId + 1;
    }
};


// 库存类
class Inventory {
private:
    int goodsId;
    int quantity;
    int alarmThreshold;

public:
    Inventory(int goodsId, int quantity, int alarmThreshold)
            : goodsId(goodsId), quantity(quantity), alarmThreshold(alarmThreshold) {}

    // 获取库存信息
    int getGoodsId() const { return goodsId; }
    int getQuantity() const { return quantity; }
    int getAlarmThreshold() const { return alarmThreshold; }

    // 设置库存信息
    void setQuantity(int quantity) { this->quantity = quantity; }
    void setAlarmThreshold(int threshold) { this->alarmThreshold = threshold; }

    // 增加库存
    void increaseQuantity(int amount) {
        quantity += amount;
    }

    // 减少库存
    bool decreaseQuantity(int amount) {
        if (quantity >= amount) {
            quantity -= amount;
            return true;
        }
        return false; // 库存不足
    }

    // 检查是否需要报警
    bool needAlarm() const {
        return quantity < alarmThreshold;
    }

    // 转换为CSV格式字符串
    string toCsvString() const {
        return to_string(goodsId) + "," +
               to_string(quantity) + "," +
               to_string(alarmThreshold);
    }

    // 从CSV格式字符串创建库存对象
    static Inventory fromCsvString(const string& csvString) {
        vector<string> tokens = StringHelper::split(csvString, ',');

        if (tokens.size() < 3) {
            return Inventory(0, 0, 0);
        }

        return Inventory(
                stoi(tokens[0]),     // 商品ID
                stoi(tokens[1]),     // 数量
                stoi(tokens[2])      // 报警阈值
        );
    }
};

// 库存管理类
class InventoryManager {
private:
    vector<Inventory> inventories;
    const string filename = "inventory.txt";

    // 加载库存数据
    void loadInventories() {
        inventories.clear();

        if (!FileHelper::fileExists(filename)) {
            return;
        }

        string content;
        if (!FileHelper::readTextFile(filename, content)) {
            return;
        }

        vector<string> lines = StringHelper::split(content, '\n');
        for (const auto& line : lines) {
            if (!line.empty()) {
                inventories.push_back(Inventory::fromCsvString(line));
            }
        }
    }

    // 保存库存数据
    void saveInventories() const {
        string content;
        for (const auto& inventory : inventories) {
            content += inventory.toCsvString() + "\n";
        }

        FileHelper::writeTextFile(filename, content);
    }

public:
    InventoryManager() {
        loadInventories();
    }

    // 添加库存记录
    bool addInventory(const Inventory& inventory) {
        // 检查商品ID是否已存在
        for (const auto& inv : inventories) {
            if (inv.getGoodsId() == inventory.getGoodsId()) {
                return false; // 商品ID重复
            }
        }

        inventories.push_back(inventory);
        saveInventories();
        return true;
    }

    // 修改库存信息
    bool updateInventory(int goodsId, const Inventory& updatedInventory) {
        for (auto& inv : inventories) {
            if (inv.getGoodsId() == goodsId) {
                inv = updatedInventory;
                saveInventories();
                return true;
            }
        }
        return false; // 未找到该商品的库存记录
    }

    // 删除库存记录
    bool deleteInventory(int goodsId) {
        for (auto it = inventories.begin(); it != inventories.end(); ++it) {
            if (it->getGoodsId() == goodsId) {
                inventories.erase(it);
                saveInventories();
                return true;
            }
        }
        return false; // 未找到该商品的库存记录
    }

    // 查找库存记录
    Inventory* findInventoryByGoodsId(int goodsId) {
        for (auto& inv : inventories) {
            if (inv.getGoodsId() == goodsId) {
                return &inv;
            }
        }
        return nullptr;
    }

    // 获取所有库存记录
    const vector<Inventory>& getAllInventories() const {
        return inventories;
    }

    // 获取需要报警的库存记录
    vector<Inventory> getAlarmInventories() const {
        vector<Inventory> result;
        for (const auto& inv : inventories) {
            if (inv.needAlarm()) {
                result.push_back(inv);
            }
        }
        return result;
    }
};


// 交易类型枚举
enum TransactionType { PURCHASE, SALE };

// 交易记录类
class Transaction {
private:
    int goodsId;
    int quantity;
    int price;
    Date date;
    int employeeId;
    TransactionType type;

public:
    Transaction(int goodsId, int quantity, int price, const Date& date, int employeeId, TransactionType type)
            : goodsId(goodsId), quantity(quantity), price(price), date(date), employeeId(employeeId), type(type) {}

    // 获取交易信息
    int getGoodsId() const { return goodsId; }
    int getQuantity() const { return quantity; }
    int getPrice() const { return price; }
    Date getDate() const { return date; }
    int getEmployeeId() const { return employeeId; }
    TransactionType getType() const { return type; }

    // 计算交易金额
    int getAmount() const {
        return quantity * price;
    }

    // 转换为CSV格式字符串
    string toCsvString() const {
        string typeStr = (type == PURCHASE) ? "PURCHASE" : "SALE";

        return to_string(goodsId) + "," +
               to_string(quantity) + "," +
               to_string(price) + "," +
               date.toString() + "," +
               to_string(employeeId) + "," +
               typeStr;
    }

    // 从CSV格式字符串创建交易记录对象
    static Transaction fromCsvString(const string& csvString) {
        vector<string> tokens = StringHelper::split(csvString, ',');

        if (tokens.size() < 6) {
            return Transaction(0, 0, 0, Date(), 0, PURCHASE);
        }

        // 解析交易类型
        TransactionType type = PURCHASE;
        if (tokens[5] == "SALE") type = SALE;

        return Transaction(
                stoi(tokens[0]),     // 商品ID
                stoi(tokens[1]),     // 数量
                stoi(tokens[2]),     // 价格
                Date::fromString(tokens[3]), // 日期
                stoi(tokens[4]),     // 员工ID
                type                 // 交易类型
        );
    }
};

// 交易记录管理类
class TransactionManager {
private:
    vector<Transaction> transactions;
    const string filename = "transactions.txt";

    // 加载交易记录
    void loadTransactions() {
        transactions.clear();

        if (!FileHelper::fileExists(filename)) {
            return;
        }

        string content;
        if (!FileHelper::readTextFile(filename, content)) {
            return;
        }

        vector<string> lines = StringHelper::split(content, '\n');
        for (const auto& line : lines) {
            if (!line.empty()) {
                transactions.push_back(Transaction::fromCsvString(line));
            }
        }
    }

    // 保存交易记录
    void saveTransactions() const {
        string content;
        for (const auto& transaction : transactions) {
            content += transaction.toCsvString() + "\n";
        }

        FileHelper::writeTextFile(filename, content);
    }

public:
    TransactionManager() {
        loadTransactions();
    }

    // 添加交易记录
    void addTransaction(const Transaction& transaction) {
        transactions.push_back(transaction);
        saveTransactions();
    }

    // 获取所有交易记录
    const vector<Transaction>& getAllTransactions() const {
        return transactions;
    }

    // 获取商品的交易记录
    vector<Transaction> getTransactionsByGoodsId(int goodsId) const {
        vector<Transaction> result;
        for (const auto& transaction : transactions) {
            if (transaction.getGoodsId() == goodsId) {
                result.push_back(transaction);
            }
        }
        return result;
    }

    // 获取员工的销售记录
    vector<Transaction> getSalesByEmployeeId(int employeeId) const {
        vector<Transaction> result;
        for (const auto& transaction : transactions) {
            if (transaction.getType() == SALE && transaction.getEmployeeId() == employeeId) {
                result.push_back(transaction);
            }
        }
        return result;
    }

    // 计算总销售额
    int getTotalSalesAmount() const {
        int total = 0;
        for (const auto& transaction : transactions) {
            if (transaction.getType() == SALE) {
                total += transaction.getAmount();
            }
        }
        return total;
    }

    // 计算总进货额
    int getTotalPurchaseAmount() const {
        int total = 0;
        for (const auto& transaction : transactions) {
            if (transaction.getType() == PURCHASE) {
                total += transaction.getAmount();
            }
        }
        return total;
    }
};


// 工作记录类
class WorkRecord {
private:
    int employeeId;
    Date startTime;
    Date endTime;
    Date paymentDate;

public:
    WorkRecord(int employeeId, const Date& startTime, const Date& endTime, const Date& paymentDate)
            : employeeId(employeeId), startTime(startTime), endTime(endTime), paymentDate(paymentDate) {}

    // 获取工作记录信息
    int getEmployeeId() const { return employeeId; }
    Date getStartTime() const { return startTime; }
    Date getEndTime() const { return endTime; }
    Date getPaymentDate() const { return paymentDate; }

    // 设置工作记录信息
    void setEndTime(const Date& endTime) { this->endTime = endTime; }
    void setPaymentDate(const Date& paymentDate) { this->paymentDate = paymentDate; }

    // 计算工作时长（小时）
    int calculateWorkingHours() const {
        // 简化计算，假设每天工作8小时
        // 实际应用中应根据具体的开始和结束时间计算
        int days = (endTime.getYear() - startTime.getYear()) * 365 +
                   (endTime.getMonth() - startTime.getMonth()) * 30 +
                   (endTime.getDay() - startTime.getDay());

        return days * 8; // 每天工作8小时
    }

    // 转换为CSV格式字符串
    string toCsvString() const {
        return to_string(employeeId) + "," +
               startTime.toString() + "," +
               endTime.toString() + "," +
               paymentDate.toString();
    }

    // 从CSV格式字符串创建工作记录对象
    static WorkRecord fromCsvString(const string& csvString) {
        vector<string> tokens = StringHelper::split(csvString, ',');

        if (tokens.size() < 4) {
            return WorkRecord(0, Date(), Date(), Date());
        }

        return WorkRecord(
                stoi(tokens[0]),     // 员工ID
                Date::fromString(tokens[1]), // 开始时间
                Date::fromString(tokens[2]), // 结束时间
                Date::fromString(tokens[3])  // 支付时间
        );
    }
};

// 工作记录管理类
class WorkRecordManager {
private:
    vector<WorkRecord> workRecords;
    const string filename = "workrecords.txt";

    // 加载工作记录
    void loadWorkRecords() {
        workRecords.clear();

        if (!FileHelper::fileExists(filename)) {
            return;
        }

        string content;
        if (!FileHelper::readTextFile(filename, content)) {
            return;
        }

        vector<string> lines = StringHelper::split(content, '\n');
        for (const auto& line : lines) {
            if (!line.empty()) {
                workRecords.push_back(WorkRecord::fromCsvString(line));
            }
        }
    }

    // 保存工作记录
    void saveWorkRecords() const {
        string content;
        for (const auto& record : workRecords) {
            content += record.toCsvString() + "\n";
        }

        FileHelper::writeTextFile(filename, content);
    }

public:
    WorkRecordManager() {
        loadWorkRecords();
    }

    // 添加工作记录
    void addWorkRecord(const WorkRecord& record) {
        workRecords.push_back(record);
        saveWorkRecords();
    }

    // 修改工作记录
    bool updateWorkRecord(int employeeId, const Date& startTime, const WorkRecord& updatedRecord) {
        for (auto& record : workRecords) {
            if (record.getEmployeeId() == employeeId && record.getStartTime() == startTime) {
                record = updatedRecord;
                saveWorkRecords();
                return true;
            }
        }
        return false;
    }

    // 获取员工的工作记录
    vector<WorkRecord> getWorkRecordsByEmployeeId(int employeeId) const {
        vector<WorkRecord> result;
        for (const auto& record : workRecords) {
            if (record.getEmployeeId() == employeeId) {
                result.push_back(record);
            }
        }
        return result;
    }

    // 计算员工的总工作时长
    int calculateTotalWorkingHours(int employeeId) const {
        int totalHours = 0;
        for (const auto& record : workRecords) {
            if (record.getEmployeeId() == employeeId) {
                totalHours += record.calculateWorkingHours();
            }
        }
        return totalHours;
    }

    // 计算员工的总工资
    int calculateTotalWage(int employeeId, int hourlyWage) const {
        return calculateTotalWorkingHours(employeeId) * hourlyWage;
    }

    // 计算所有员工的总工资
    int calculateTotalWageForAllEmployees(const EmployeeManager& employeeManager) const {
        int totalWage = 0;

        const vector<Employee>& employees = employeeManager.getAllEmployees();
        for (const auto& employee : employees) {
            totalWage += calculateTotalWage(employee.getId(), employee.getHourlyWage());
        }

        return totalWage;
    }
};

// 财务管理类
class FinancialManager {
private:
    int totalAmount; // 总金额
    const string filename = "financial.txt";
    TransactionManager* transactionManager;
    WorkRecordManager* workRecordManager;
    EmployeeManager* employeeManager;

    // 加载财务数据
    void loadFinancialData() {
        if (!FileHelper::fileExists(filename)) {
            totalAmount = 100000; // 默认启动资金10万元
            saveFinancialData();
            return;
        }

        string content;
        if (!FileHelper::readTextFile(filename, content)) {
            totalAmount = 100000; // 默认启动资金10万元
            return;
        }

        try {
            totalAmount = stoi(content);
        } catch (...) {
            totalAmount = 100000; // 默认启动资金10万元
        }
    }

    // 保存财务数据
    void saveFinancialData() const {
        FileHelper::writeTextFile(filename, to_string(totalAmount));
    }

public:
    FinancialManager(TransactionManager* transactionManager,
                     WorkRecordManager* workRecordManager,
                     EmployeeManager* employeeManager)
            : transactionManager(transactionManager),
              workRecordManager(workRecordManager),
              employeeManager(employeeManager) {
        loadFinancialData();
    }

    // 获取当前总金额
    int getTotalAmount() const {
        return totalAmount;
    }

    // 获取总销售额
    int getTotalSales() const {
        return transactionManager->getTotalSalesAmount();
    }

    // 获取总进货额
    int getTotalPurchase() const {
        return transactionManager->getTotalPurchaseAmount();
    }

    // 获取总工资
    int getTotalWage() const {
        return workRecordManager->calculateTotalWageForAllEmployees(*employeeManager);
    }

    // 获取总利润
    int getTotalProfit() const {
        return getTotalSales() - getTotalPurchase() - getTotalWage();
    }

    // 记录进货支出
    void recordPurchaseExpense(int amount) {
        totalAmount -= amount;
        saveFinancialData();
    }

    // 记录销售收入
    void recordSalesIncome(int amount) {
        totalAmount += amount;
        saveFinancialData();
    }

    // 记录工资支出
    void recordWageExpense(int amount) {
        totalAmount -= amount;
        saveFinancialData();
    }
};


// 小店管理系统主类
class ShopManagementSystem {
private:
    UserManager userManager;
    EmployeeManager employeeManager;
    SupplierManager supplierManager;
    GoodsManager goodsManager;
    InventoryManager inventoryManager;
    TransactionManager transactionManager;
    WorkRecordManager workRecordManager;
    FinancialManager financialManager;

    // 登录界面
    bool loginScreen() {
        string username, password;

        while (true) {
            cout << "========== 登录系统 ==========" << endl;
            cout << "请输入用户名: ";
            cin >> username;
            cout << "请输入密码: ";
            cin >> password;

            if (userManager.login(username, password)) {
                cout << "登录成功！" << endl;
                return true;
            } else {
                cout << "用户名或密码错误，请重新输入！" << endl;
            }
        }
    }

    // 主界面
    void mainScreen() {
        while (true) {
            cout << "\n========== 主界面 ==========" << endl;
            cout << "1. 员工管理" << endl;
            cout << "2. 供应商管理" << endl;
            cout << "3. 商品管理" << endl;
            cout << "4. 库存管理" << endl;
            cout << "5. 进货管理" << endl;
            cout << "6. 销售管理" << endl;
            cout << "7. 财务管理" << endl;
            cout << "8. 退出程序" << endl;
            cout << "请选择操作: ";

            int choice;
            cin >> choice;
            cin.ignore(); // 清除输入缓冲区

            switch (choice) {
                case 1:
                    if (userManager.getCurrentUserRole() == MANAGER) {
                        employeeManagementScreen();
                    } else {
                        cout << "权限不足！" << endl;
                    }
                    break;
                case 2:
                    if (userManager.getCurrentUserRole() == MANAGER) {
                        supplierManagementScreen();
                    } else {
                        cout << "权限不足！" << endl;
                    }
                    break;
                case 3:
                    if (userManager.getCurrentUserRole() == MANAGER) {
                        goodsManagementScreen();
                    } else {
                        cout << "权限不足！" << endl;
                    }
                    break;
                case 4:
                    if (userManager.getCurrentUserRole() == MANAGER) {
                        inventoryManagementScreen();
                    } else {
                        cout << "权限不足！" << endl;
                    }
                    break;
                case 5:
                    if (userManager.getCurrentUserRole() == MANAGER) {
                        purchaseManagementScreen();
                    } else {
                        cout << "权限不足！" << endl;
                    }
                    break;
                case 6:
                    salesManagementScreen();
                    break;
                case 7:
                    if (userManager.getCurrentUserRole() == MANAGER) {
                        financialManagementScreen();
                    } else {
                        cout << "权限不足！" << endl;
                    }
                    break;
                case 8:
                    cout << "感谢使用小店管理系统，再见！" << endl;
                    return;
                default:
                    cout << "无效选择，请重新输入！" << endl;
            }
        }
    }

    // 员工管理界面
    void employeeManagementScreen() {
        while (true) {
            cout << "\n========== 员工管理 ==========" << endl;
            cout << "1. 添加员工" << endl;
            cout << "2. 修改员工信息" << endl;
            cout << "3. 删除员工" << endl;
            cout << "4. 查找员工" << endl;
            cout << "5. 查看所有员工" << endl;
            cout << "6. 返回主界面" << endl;
            cout << "请选择操作: ";

            int choice;
            cin >> choice;
            cin.ignore(); // 清除输入缓冲区

            switch (choice) {
                case 1:
                    addEmployee();
                    break;
                case 2:
                    updateEmployee();
                    break;
                case 3:
                    deleteEmployee();
                    break;
                case 4:
                    findEmployee();
                    break;
                case 5:
                    viewAllEmployees();
                    break;
                case 6:
                    return;
                default:
                    cout << "无效选择，请重新输入！" << endl;
            }
        }
    }

    // 添加员工
    void addEmployee() {
        cout << "\n========== 添加员工 ==========" << endl;

        int id = employeeManager.getNextEmployeeId();
        string name, idCard, hometown, ethnicity, college, className, address, phone, username, password, notes;
        Gender gender;
        Date birthDate;
        int hourlyWage;
        int genderChoice;

        cout << "姓名: ";
        getline(cin, name);

        cout << "身份证号: ";
        getline(cin, idCard);

        cout << "性别 (1: 男, 2: 女, 3: 其他): ";
        cin >> genderChoice;
        cin.ignore();

        switch (genderChoice) {
            case 1: gender = MALE; break;
            case 2: gender = FEMALE; break;
            case 3: gender = OTHER; break;
            default: gender = MALE;
        }

        string birthDateStr;
        cout << "出生日期 (YYYY-MM-DD): ";
        getline(cin, birthDateStr);
        birthDate = Date::fromString(birthDateStr);

        cout << "籍贯: ";
        getline(cin, hometown);

        cout << "民族: ";
        getline(cin, ethnicity);

        cout << "学院: ";
        getline(cin, college);

        cout << "班级: ";
        getline(cin, className);

        cout << "地址: ";
        getline(cin, address);

        cout << "电话: ";
        getline(cin, phone);

        cout << "小时工资: ";
        cin >> hourlyWage;
        cin.ignore();

        cout << "用户名: ";
        getline(cin, username);

        cout << "密码: ";
        getline(cin, password);

        cout << "备注: ";
        getline(cin, notes);

        Employee newEmployee(id, name, idCard, gender, birthDate, hometown, ethnicity,
                             college, className, address, phone, hourlyWage, username, password, notes);

        if (employeeManager.addEmployee(newEmployee)) {
            cout << "员工添加成功！" << endl;
        } else {
            cout << "员工添加失败：身份证号重复！" << endl;
        }
    }

    // 修改员工信息
    void updateEmployee() {
        cout << "\n========== 修改员工信息 ==========" << endl;
        cout << "请输入要修改的员工ID: ";
        int id;
        cin >> id;
        cin.ignore();

        Employee* employee = employeeManager.findEmployeeById(id);
        if (!employee) {
            cout << "未找到该员工！" << endl;
            return;
        }

        string name, idCard, hometown, ethnicity, college, className, address, phone, username, password, notes;
        Gender gender;
        Date birthDate;
        int hourlyWage;
        int genderChoice;

        cout << "姓名 (" << employee->getName() << "): ";
        getline(cin, name);
        if (!name.empty()) employee->setName(name);

        cout << "身份证号 (" << employee->getIdCard() << "): ";
        getline(cin, idCard);
        if (!idCard.empty()) employee->setIdCard(idCard);

        cout << "性别 (" << (employee->getGender() == MALE ? "男" : employee->getGender() == FEMALE ? "女" : "其他") << "): ";
        cin >> genderChoice;
        cin.ignore();

        if (genderChoice >= 1 && genderChoice <= 3) {
            switch (genderChoice) {
                case 1: gender = MALE; break;
                case 2: gender = FEMALE; break;
                case 3: gender = OTHER; break;
                default: gender = MALE;
            }
            employee->setGender(gender);
        }

        string birthDateStr;
        cout << "出生日期 (" << employee->getBirthDate().toString() << "): ";
        getline(cin, birthDateStr);
        if (!birthDateStr.empty()) {
            birthDate = Date::fromString(birthDateStr);
            if (birthDate.isValid()) {
                employee->setBirthDate(birthDate);
            }
        }

        cout << "籍贯 (" << employee->getHometown() << "): ";
        getline(cin, hometown);
        if (!hometown.empty()) employee->setHometown(hometown);

        cout << "民族 (" << employee->getEthnicity() << "): ";
        getline(cin, ethnicity);
        if (!ethnicity.empty()) employee->setEthnicity(ethnicity);

        cout << "学院 (" << employee->getCollege() << "): ";
        getline(cin, college);
        if (!college.empty()) employee->setCollege(college);

        cout << "班级 (" << employee->getClassName() << "): ";
        getline(cin, className);
        if (!className.empty()) employee->setClassName(className);

        cout << "地址 (" << employee->getAddress() << "): ";
        getline(cin, address);
        if (!address.empty()) employee->setAddress(address);

        cout << "电话 (" << employee->getPhone() << "): ";
        getline(cin, phone);
        if (!phone.empty()) employee->setPhone(phone);

        cout << "小时工资 (" << employee->getHourlyWage() << "): ";
        cin >> hourlyWage;
        cin.ignore();
        if (hourlyWage > 0) employee->setHourlyWage(hourlyWage);

        cout << "用户名 (" << employee->getUsername() << "): ";
        getline(cin, username);
        if (!username.empty()) employee->setUsername(username);

        cout << "密码: ";
        getline(cin, password);
        if (!password.empty()) employee->setPassword(password);

        cout << "备注 (" << employee->getNotes() << "): ";
        getline(cin, notes);
        if (!notes.empty()) employee->setNotes(notes);

        if (employeeManager.updateEmployee(id, *employee)) {
            cout << "员工信息修改成功！" << endl;
        } else {
            cout << "员工信息修改失败：身份证号重复！" << endl;
        }
    }

    // 删除员工
    void deleteEmployee() {
        cout << "\n========== 删除员工 ==========" << endl;
        cout << "请输入要删除的员工ID: ";
        int id;
        cin >> id;
        cin.ignore();

        if (employeeManager.deleteEmployee(id)) {
            cout << "员工删除成功！" << endl;
        } else {
            cout << "员工删除失败：未找到该员工！" << endl;
        }
    }

    // 查找员工
    void findEmployee() {
        cout << "\n========== 查找员工 ==========" << endl;
        cout << "请选择查找方式: " << endl;
        cout << "1. 按ID查找" << endl;
        cout << "2. 按身份证号查找" << endl;
        cout << "请选择: ";

        int choice;
        cin >> choice;
        cin.ignore();

        Employee* employee = nullptr;

        if (choice == 1) {
            cout << "请输入员工ID: ";
            int id;
            cin >> id;
            cin.ignore();
            employee = employeeManager.findEmployeeById(id);
        } else if (choice == 2) {
            cout << "请输入身份证号: ";
            string idCard;
            getline(cin, idCard);
            employee = employeeManager.findEmployeeByIdCard(idCard);
        } else {
            cout << "无效选择！" << endl;
            return;
        }

        if (employee) {
            cout << "\n员工信息:" << endl;
            cout << "ID: " << employee->getId() << endl;
            cout << "姓名: " << employee->getName() << endl;
            cout << "身份证号: " << employee->getIdCard() << endl;
            cout << "性别: " << (employee->getGender() == MALE ? "男" : employee->getGender() == FEMALE ? "女" : "其他") << endl;
            cout << "出生日期: " << employee->getBirthDate().toString() << endl;
            cout << "籍贯: " << employee->getHometown() << endl;
            cout << "民族: " << employee->getEthnicity() << endl;
            cout << "学院: " << employee->getCollege() << endl;
            cout << "班级: " << employee->getClassName() << endl;
            cout << "地址: " << employee->getAddress() << endl;
            cout << "电话: " << employee->getPhone() << endl;
            cout << "小时工资: " << employee->getHourlyWage() << endl;
            cout << "用户名: " << employee->getUsername() << endl;
            cout << "备注: " << employee->getNotes() << endl;
        } else {
            cout << "未找到该员工！" << endl;
        }
    }

    // 查看所有员工
    void viewAllEmployees() {
        cout << "\n========== 所有员工 ==========" << endl;

        const vector<Employee>& employees = employeeManager.getAllEmployees();

        if (employees.empty()) {
            cout << "暂无员工记录！" << endl;
            return;
        }

        cout << "ID\t姓名\t身份证号\t性别\t出生日期\t籍贯\t民族\t学院\t班级\t地址\t电话\t小时工资\t用户名\t备注" << endl;
        for (const auto& employee : employees) {
            cout << employee.getId() << "\t"
                 << employee.getName() << "\t"
                 << employee.getIdCard() << "\t"
                 << (employee.getGender() == MALE ? "男" : employee.getGender() == FEMALE ? "女" : "其他") << "\t"
                 << employee.getBirthDate().toString() << "\t"
                 << employee.getHometown() << "\t"
                 << employee.getEthnicity() << "\t"
                 << employee.getCollege() << "\t"
                 << employee.getClassName() << "\t"
                 << employee.getAddress() << "\t"
                 << employee.getPhone() << "\t"
                 << employee.getHourlyWage() << "\t"
                 << employee.getUsername() << "\t"
                 << employee.getNotes() << endl;
        }
    }

    // 供应商管理界面
    void supplierManagementScreen() {
        while (true) {
            cout << "\n========== 供应商管理 ==========" << endl;
            cout << "1. 添加供应商" << endl;
            cout << "2. 修改供应商信息" << endl;
            cout << "3. 删除供应商" << endl;
            cout << "4. 查找供应商" << endl;
            cout << "5. 查看所有供应商" << endl;
            cout << "6. 返回主界面" << endl;
            cout << "请选择操作: ";

            int choice;
            cin >> choice;
            cin.ignore(); // 清除输入缓冲区

            switch (choice) {
                case 1:
                    addSupplier();
                    break;
                case 2:
                    updateSupplier();
                    break;
                case 3:
                    deleteSupplier();
                    break;
                case 4:
                    findSupplier();
                    break;
                case 5:
                    viewAllSuppliers();
                    break;
                case 6:
                    return;
                default:
                    cout << "无效选择，请重新输入！" << endl;
            }
        }
    }

    // 添加供应商
    void addSupplier() {
        cout << "\n========== 添加供应商 ==========" << endl;

        int id = supplierManager.getNextSupplierId();
        string name, phone, address, notes;

        cout << "供应商名称: ";
        getline(cin, name);

        cout << "供应商电话: ";
        getline(cin, phone);

        cout << "供应商地址: ";
        getline(cin, address);

        cout << "供应商备注: ";
        getline(cin, notes);

        Supplier newSupplier(id, name, phone, address, notes);

        if (supplierManager.addSupplier(newSupplier)) {
            cout << "供应商添加成功！" << endl;
        } else {
            cout << "供应商添加失败！" << endl;
        }
    }

    // 修改供应商信息
    void updateSupplier() {
        cout << "\n========== 修改供应商信息 ==========" << endl;
        cout << "请输入要修改的供应商ID: ";
        int id;
        cin >> id;
        cin.ignore();

        Supplier* supplier = supplierManager.findSupplierById(id);
        if (!supplier) {
            cout << "未找到该供应商！" << endl;
            return;
        }

        string name, phone, address, notes;

        cout << "供应商名称 (" << supplier->getName() << "): ";
        getline(cin, name);
        if (!name.empty()) supplier->setName(name);

        cout << "供应商电话 (" << supplier->getPhone() << "): ";
        getline(cin, phone);
        if (!phone.empty()) supplier->setPhone(phone);

        cout << "供应商地址 (" << supplier->getAddress() << "): ";
        getline(cin, address);
        if (!address.empty()) supplier->setAddress(address);

        cout << "供应商备注 (" << supplier->getNotes() << "): ";
        getline(cin, notes);
        if (!notes.empty()) supplier->setNotes(notes);

        if (supplierManager.updateSupplier(id, *supplier)) {
            cout << "供应商信息修改成功！" << endl;
        } else {
            cout << "供应商信息修改失败！" << endl;
        }
    }

    // 删除供应商
    void deleteSupplier() {
        cout << "\n========== 删除供应商 ==========" << endl;
        cout << "请输入要删除的供应商ID: ";
        int id;
        cin >> id;
        cin.ignore();

        if (supplierManager.deleteSupplier(id)) {
            cout << "供应商删除成功！" << endl;
        } else {
            cout << "供应商删除失败：未找到该供应商！" << endl;
        }
    }

    // 查找供应商
    void findSupplier() {
        cout << "\n========== 查找供应商 ==========" << endl;
        cout << "请输入供应商ID: ";
        int id;
        cin >> id;
        cin.ignore();

        Supplier* supplier = supplierManager.findSupplierById(id);

        if (supplier) {
            cout << "\n供应商信息:" << endl;
            cout << "ID: " << supplier->getId() << endl;
            cout << "名称: " << supplier->getName() << endl;
            cout << "电话: " << supplier->getPhone() << endl;
            cout << "地址: " << supplier->getAddress() << endl;
            cout << "备注: " << supplier->getNotes() << endl;
        } else {
            cout << "未找到该供应商！" << endl;
        }
    }

    // 查看所有供应商
    void viewAllSuppliers() {
        cout << "\n========== 所有供应商 ==========" << endl;

        const vector<Supplier>& suppliers = supplierManager.getAllSuppliers();

        if (suppliers.empty()) {
            cout << "暂无供应商记录！" << endl;
            return;
        }

        cout << "ID\t名称\t电话\t地址\t备注" << endl;
        for (const auto& supplier : suppliers) {
            cout << supplier.getId() << "\t"
                 << supplier.getName() << "\t"
                 << supplier.getPhone() << "\t"
                 << supplier.getAddress() << "\t"
                 << supplier.getNotes() << endl;
        }
    }

    // 商品管理界面
    void goodsManagementScreen() {
        while (true) {
            cout << "\n========== 商品管理 ==========" << endl;
            cout << "1. 添加商品" << endl;
            cout << "2. 修改商品信息" << endl;
            cout << "3. 删除商品" << endl;
            cout << "4. 查找商品" << endl;
            cout << "5. 查看所有商品" << endl;
            cout << "6. 返回主界面" << endl;
            cout << "请选择操作: ";

            int choice;
            cin >> choice;
            cin.ignore(); // 清除输入缓冲区

            switch (choice) {
                case 1:
                    addGoods();
                    break;
                case 2:
                    updateGoods();
                    break;
                case 3:
                    deleteGoods();
                    break;
                case 4:
                    findGoods();
                    break;
                case 5:
                    viewAllGoods();
                    break;
                case 6:
                    return;
                default:
                    cout << "无效选择，请重新输入！" << endl;
            }
        }
    }

    // 添加商品
    void addGoods() {
        cout << "\n========== 添加商品 ==========" << endl;

        int id = goodsManager.getNextGoodsId();
        string name;
        int supplierId;

        cout << "商品名称: ";
        getline(cin, name);

        cout << "供应商ID: ";
        cin >> supplierId;
        cin.ignore();

        Supplier* supplier = supplierManager.findSupplierById(supplierId);
        if (!supplier) {
            cout << "供应商不存在！" << endl;
            return;
        }

        Goods newGoods(id, name, supplierId);

        if (goodsManager.addGoods(newGoods)) {
            // 同时添加库存记录
            Inventory newInventory(id, 0, 10); // 默认库存0，报警阈值10
            inventoryManager.addInventory(newInventory);

            cout << "商品添加成功！" << endl;
        } else {
            cout << "商品添加失败！" << endl;
        }
    }

    // 修改商品信息
    void updateGoods() {
        cout << "\n========== 修改商品信息 ==========" << endl;
        cout << "请输入要修改的商品ID: ";
        int id;
        cin >> id;
        cin.ignore();

        Goods* goods = goodsManager.findGoodsById(id);
        if (!goods) {
            cout << "未找到该商品！" << endl;
            return;
        }

        string name;
        int supplierId;

        cout << "商品名称 (" << goods->getName() << "): ";
        getline(cin, name);
        if (!name.empty()) goods->setName(name);

        cout << "供应商ID (" << goods->getSupplierId() << "): ";
        cin >> supplierId;
        cin.ignore();

        if (supplierId > 0) {
            Supplier* supplier = supplierManager.findSupplierById(supplierId);
            if (!supplier) {
                cout << "供应商不存在！" << endl;
            } else {
                goods->setSupplierId(supplierId);
            }
        }

        if (goodsManager.updateGoods(id, *goods)) {
            cout << "商品信息修改成功！" << endl;
        } else {
            cout << "商品信息修改失败！" << endl;
        }
    }

    // 删除商品
    void deleteGoods() {
        cout << "\n========== 删除商品 ==========" << endl;
        cout << "请输入要删除的商品ID: ";
        int id;
        cin >> id;
        cin.ignore();

        // 先删除库存记录
        inventoryManager.deleteInventory(id);

        if (goodsManager.deleteGoods(id)) {
            cout << "商品删除成功！" << endl;
        } else {
            cout << "商品删除失败：未找到该商品！" << endl;
        }
    }

    // 查找商品
    void findGoods() {
        cout << "\n========== 查找商品 ==========" << endl;
        cout << "请输入商品ID: ";
        int id;
        cin >> id;
        cin.ignore();

        Goods* goods = goodsManager.findGoodsById(id);

        if (goods) {
            Supplier* supplier = supplierManager.findSupplierById(goods->getSupplierId());
            string supplierName = supplier ? supplier->getName() : "未知供应商";

            cout << "\n商品信息:" << endl;
            cout << "ID: " << goods->getId() << endl;
            cout << "名称: " << goods->getName() << endl;
            cout << "供应商: " << supplierName << " (ID: " << goods->getSupplierId() << ")" << endl;

            // 显示库存信息
            Inventory* inventory = inventoryManager.findInventoryByGoodsId(id);
            if (inventory) {
                cout << "库存数量: " << inventory->getQuantity() << endl;
                cout << "报警阈值: " << inventory->getAlarmThreshold() << endl;
                cout << (inventory->needAlarm() ? "需要进货！" : "库存充足") << endl;
            }
        } else {
            cout << "未找到该商品！" << endl;
        }
    }

    // 查看所有商品
    void viewAllGoods() {
        cout << "\n========== 所有商品 ==========" << endl;

        const vector<Goods>& goodsList = goodsManager.getAllGoods();

        if (goodsList.empty()) {
            cout << "暂无商品记录！" << endl;
            return;
        }

        cout << "ID\t名称\t供应商ID" << endl;
        for (const auto& goods : goodsList) {
            cout << goods.getId() << "\t"
                 << goods.getName() << "\t"
                 << goods.getSupplierId() << endl;
        }
    }

    // 库存管理界面
    void inventoryManagementScreen() {
        while (true) {
            cout << "\n========== 库存管理 ==========" << endl;
            cout << "1. 显示库存" << endl;
            cout << "2. 修改库存报警数量" << endl;
            cout << "3. 查看需要进货的商品" << endl;
            cout << "4. 返回主界面" << endl;
            cout << "请选择操作: ";

            int choice;
            cin >> choice;
            cin.ignore(); // 清除输入缓冲区

            switch (choice) {
                case 1:
                    viewAllInventories();
                    break;
                case 2:
                    updateInventoryAlarmThreshold();
                    break;
                case 3:
                    viewAlarmInventories();
                    break;
                case 4:
                    return;
                default:
                    cout << "无效选择，请重新输入！" << endl;
            }
        }
    }

    // 显示所有库存
    void viewAllInventories() {
        cout << "\n========== 所有库存 ==========" << endl;

        const vector<Inventory>& inventories = inventoryManager.getAllInventories();

        if (inventories.empty()) {
            cout << "暂无库存记录！" << endl;
            return;
        }

        cout << "商品ID\t商品名称\t库存数量\t报警阈值\t状态" << endl;
        for (const auto& inventory : inventories) {
            Goods* goods = goodsManager.findGoodsById(inventory.getGoodsId());
            string goodsName = goods ? goods->getName() : "未知商品";
            string status = inventory.needAlarm() ? "需要进货" : "库存充足";

            cout << inventory.getGoodsId() << "\t"
                 << goodsName << "\t"
                 << inventory.getQuantity() << "\t"
                 << inventory.getAlarmThreshold() << "\t"
                 << status << endl;
        }
    }

    // 修改库存报警数量
    void updateInventoryAlarmThreshold() {
        cout << "\n========== 修改库存报警数量 ==========" << endl;
        cout << "请输入商品ID: ";
        int goodsId;
        cin >> goodsId;
        cin.ignore();

        Inventory* inventory = inventoryManager.findInventoryByGoodsId(goodsId);
        if (!inventory) {
            cout << "未找到该商品的库存记录！" << endl;
            return;
        }

        Goods* goods = goodsManager.findGoodsById(goodsId);
        string goodsName = goods ? goods->getName() : "未知商品";

        cout << "商品: " << goodsName << " (ID: " << goodsId << ")" << endl;
        cout << "当前报警阈值: " << inventory->getAlarmThreshold() << endl;
        cout << "请输入新的报警阈值: ";

        int newThreshold;
        cin >> newThreshold;
        cin.ignore();

        inventory->setAlarmThreshold(newThreshold);

        if (inventoryManager.updateInventory(goodsId, *inventory)) {
            cout << "报警阈值修改成功！" << endl;
        } else {
            cout << "报警阈值修改失败！" << endl;
        }
    }

    // 查看需要进货的商品
    void viewAlarmInventories() {
        cout << "\n========== 需要进货的商品 ==========" << endl;

        vector<Inventory> alarmInventories = inventoryManager.getAlarmInventories();

        if (alarmInventories.empty()) {
            cout << "所有商品库存充足，无需进货！" << endl;
            return;
        }

        cout << "商品ID\t商品名称\t库存数量\t报警阈值" << endl;
        for (const auto& inventory : alarmInventories) {
            Goods* goods = goodsManager.findGoodsById(inventory.getGoodsId());
            string goodsName = goods ? goods->getName() : "未知商品";

            cout << inventory.getGoodsId() << "\t"
                 << goodsName << "\t"
                 << inventory.getQuantity() << "\t"
                 << inventory.getAlarmThreshold() << endl;
        }
    }

    // 进货管理界面
    void purchaseManagementScreen() {
        while (true) {
            cout << "\n========== 进货管理 ==========" << endl;
            cout << "1. 添加进货记录" << endl;
            cout << "2. 查看进货记录" << endl;
            cout << "3. 返回主界面" << endl;
            cout << "请选择操作: ";

            int choice;
            cin >> choice;
            cin.ignore(); // 清除输入缓冲区

            switch (choice) {
                case 1:
                    addPurchaseRecord();
                    break;
                case 2:
                    viewPurchaseRecords();
                    break;
                case 3:
                    return;
                default:
                    cout << "无效选择，请重新输入！" << endl;
            }
        }
    }

    // 添加进货记录
    void addPurchaseRecord() {
        cout << "\n========== 添加进货记录 ==========" << endl;

        int goodsId, quantity, price;
        string dateStr;

        cout << "商品ID: ";
        cin >> goodsId;
        cin.ignore();

        Goods* goods = goodsManager.findGoodsById(goodsId);
        if (!goods) {
            cout << "商品不存在！" << endl;
            return;
        }

        cout << "商品: " << goods->getName() << " (供应商ID: " << goods->getSupplierId() << ")" << endl;
        cout << "进货数量: ";
        cin >> quantity;
        cin.ignore();

        cout << "进货价格: ";
        cin >> price;
        cin.ignore();

        cout << "进货日期 (YYYY-MM-DD，默认今天): ";
        getline(cin, dateStr);

        Date date = dateStr.empty() ? Date::getCurrentDate() : Date::fromString(dateStr);

        // 添加交易记录
        Transaction transaction(goodsId, quantity, price, date, 0, PURCHASE);
        transactionManager.addTransaction(transaction);

        // 更新库存
        Inventory* inventory = inventoryManager.findInventoryByGoodsId(goodsId);
        if (inventory) {
            inventory->increaseQuantity(quantity);
            inventoryManager.updateInventory(goodsId, *inventory);
        } else {
            // 如果库存记录不存在，创建新记录
            Inventory newInventory(goodsId, quantity, 10); // 默认报警阈值10
            inventoryManager.addInventory(newInventory);
        }

        // 更新财务记录
        financialManager.recordPurchaseExpense(quantity * price);

        cout << "进货记录添加成功！" << endl;
    }

    // 查看进货记录
    void viewPurchaseRecords() {
        cout << "\n========== 进货记录 ==========" << endl;

        const vector<Transaction>& transactions = transactionManager.getAllTransactions();

        bool hasPurchaseRecords = false;

        cout << "商品ID\t商品名称\t进货数量\t进货价格\t进货日期\t供应商ID" << endl;
        for (const auto& transaction : transactions) {
            if (transaction.getType() == PURCHASE) {
                hasPurchaseRecords = true;

                Goods* goods = goodsManager.findGoodsById(transaction.getGoodsId());
                string goodsName = goods ? goods->getName() : "未知商品";
                int supplierId = goods ? goods->getSupplierId() : 0;

                cout << transaction.getGoodsId() << "\t"
                     << goodsName << "\t"
                     << transaction.getQuantity() << "\t"
                     << transaction.getPrice() << "\t"
                     << transaction.getDate().toString() << "\t"
                     << supplierId << endl;
            }
        }

        if (!hasPurchaseRecords) {
            cout << "暂无进货记录！" << endl;
        }
    }

    // 销售管理界面
    void salesManagementScreen() {
        while (true) {
            cout << "\n========== 销售管理 ==========" << endl;
            cout << "1. 添加销售记录" << endl;
            cout << "2. 查看销售记录" << endl;
            cout << "3. 返回主界面" << endl;
            cout << "请选择操作: ";

            int choice;
            cin >> choice;
            cin.ignore(); // 清除输入缓冲区

            switch (choice) {
                case 1:
                    addSalesRecord();
                    break;
                case 2:
                    viewSalesRecords();
                    break;
                case 3:
                    return;
                default:
                    cout << "无效选择，请重新输入！" << endl;
            }
        }
    }

    // 添加销售记录
    void addSalesRecord() {
        cout << "\n========== 添加销售记录 ==========" << endl;

        int goodsId, quantity, price;
        string dateStr;
        int employeeId = (userManager.getCurrentUserRole() == EMPLOYEE) ?
                         1 : 0; // 员工ID，默认管理员为0

        cout << "商品ID: ";
        cin >> goodsId;
        cin.ignore();

        Goods* goods = goodsManager.findGoodsById(goodsId);
        if (!goods) {
            cout << "商品不存在！" << endl;
            return;
        }

        Inventory* inventory = inventoryManager.findInventoryByGoodsId(goodsId);
        if (!inventory) {
            cout << "该商品无库存记录！" << endl;
            return;
        }

        cout << "商品: " << goods->getName() << " (当前库存: " << inventory->getQuantity() << ")" << endl;
        cout << "销售数量: ";
        cin >> quantity;
        cin.ignore();

        if (quantity > inventory->getQuantity()) {
            cout << "库存不足！" << endl;
            return;
        }

        cout << "销售价格: ";
        cin >> price;
        cin.ignore();

        cout << "销售日期 (YYYY-MM-DD，默认今天): ";
        getline(cin, dateStr);

        Date date = dateStr.empty() ? Date::getCurrentDate() : Date::fromString(dateStr);

        // 添加交易记录
        Transaction transaction(goodsId, quantity, price, date, employeeId, SALE);
        transactionManager.addTransaction(transaction);

        // 更新库存
        inventory->decreaseQuantity(quantity);
        inventoryManager.updateInventory(goodsId, *inventory);

        // 更新财务记录
        financialManager.recordSalesIncome(quantity * price);

        cout << "销售记录添加成功！" << endl;
    }

    // 查看销售记录
    void viewSalesRecords() {
        cout << "\n========== 销售记录 ==========" << endl;

        const vector<Transaction>& transactions = transactionManager.getAllTransactions();

        bool hasSalesRecords = false;

        cout << "商品ID\t商品名称\t销售数量\t销售价格\t销售日期\t销售员ID" << endl;
        for (const auto& transaction : transactions) {
            if (transaction.getType() == SALE) {
                hasSalesRecords = true;

                Goods* goods = goodsManager.findGoodsById(transaction.getGoodsId());
                string goodsName = goods ? goods->getName() : "未知商品";

                cout << transaction.getGoodsId() << "\t"
                     << goodsName << "\t"
                     << transaction.getQuantity() << "\t"
                     << transaction.getPrice() << "\t"
                     << transaction.getDate().toString() << "\t"
                     << transaction.getEmployeeId() << endl;
            }
        }

        if (!hasSalesRecords) {
            cout << "暂无销售记录！" << endl;
        }
    }

    // 财务管理界面
    void financialManagementScreen() {
        cout << "\n========== 财务管理 ==========" << endl;

        cout << "当前总金额: " << financialManager.getTotalAmount() << " 元" << endl;
        cout << "总销售额: " << financialManager.getTotalSales() << " 元" << endl;
        cout << "总进货额: " << financialManager.getTotalPurchase() << " 元" << endl;
        cout << "总工资: " << financialManager.getTotalWage() << " 元" << endl;
        cout << "总利润: " << financialManager.getTotalProfit() << " 元" << endl;

        cout << "\n按任意键返回..." << endl;
        cin.get();
    }

public:
    ShopManagementSystem() : financialManager(&transactionManager, &workRecordManager, &employeeManager) {
        // 初始化默认用户
        userManager.initializeDefaultUsers();
    }


    void run() {
        cout << "欢迎使用小店管理系统！" << endl;

        if (loginScreen()) {
            mainScreen();
        }
    }
};


int main() {

    SetConsoleOutputCP(65001);


    system("chcp 65001 > nul");
    ShopManagementSystem system;
    system.run();
    return 0;
}