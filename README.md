

# 基于 C++ 的小店管理系统

## 介绍

这是一个控制台版库存管理系统，采用 C++ 开发。系统集成了员工管理、供应商管理、商品管理、库存监控、交易记录、财务统计等核心功能模块，采用纯文本 CSV 格式存储数据，无需数据库依赖，开箱即用。

## 功能特性

### 用户认证
- 管理员 / 员工登录与登出
- 默认管理员账户初始化

### 员工管理
- 员工信息的新增、修改、删除、查询
- 身份证号唯一性校验
- CSV 格式数据持久化

### 供应商管理
- 供应商信息的新增、修改、删除、查询
- 供应商 ID 自动递增

### 商品管理
- 商品信息的新增、修改、删除、查询
- 商品关联供应商 ID

### 库存管理
- 库存数量增减
- 报警阈值设置
- 库存不足自动提醒

### 交易记录
- 进货 / 销售交易记录
- 按商品 / 员工查询交易
- 统计总销售额与总进货额

### 员工工作记录
- 记录员工工作时段
- 计算总工作时长

### 财务管理
- 收入与支出记录
- 员工工资统计
- 利润计算

## 技术栈

| 类别 | 说明 |
|------|------|
| 编程语言 | C++ (C++11 及以上) |
| 核心库 | C++ 标准库 (iostream/fstream/vector/map/ctime 等) |
| 数据存储 | 纯文本文件 (CSV 格式) |
| 系统依赖 | Windows API (windows.h) |

## 编译环境

- **编译器**：MinGW-w64 / MSVC / Dev-C++ / Code::Blocks
- **操作系统**：Windows 7/10/11 (32/64 位)

## 快速开始

### 编译

使用 g++ 编译：
```bash
g++ -std=c++11 manager1.cpp -o InventorySystem
```

使用 MSVC 编译：
```bash
cl /EHsc /std:c++11 manager1.cpp
```

### 运行

直接执行编译生成的 `InventorySystem.exe` 即可，程序运行时会自动检测并创建所需的文本数据文件。

## 文件结构

### 源代码
- `manager1.cpp` - 核心源代码，包含所有类定义与业务逻辑

### 数据存储文件
程序运行后自动生成以下文件：

| 文件名 | 用途 |
|--------|------|
| employee.txt | 员工信息 |
| supplier.txt | 供应商信息 |
| goodsinfo.txt | 商品信息 |
| inventory.txt | 库存信息 |
| transactions.txt | 交易记录 |
| workrecords.txt | 员工工作记录 |
| financial.txt | 财务数据 |

## 核心类架构

```
Date                    - 日期处理（解析、格式化、比较、有效性校验）
User / UserManager      - 用户认证与角色管理
Employee / EmployeeManager    - 员工信息 CRUD 操作
Supplier / SupplierManager    - 供应商信息 CRUD 操作
Goods / GoodsManager           - 商品信息 CRUD 操作
Inventory / InventoryManager   - 库存数量管理与报警
Transaction / TransactionManager - 交易记录管理
WorkRecord / WorkRecordManager  - 员工工作记录与时长计算
FinancialManager        - 财务统计管理
ShopManagementSystem    - 系统主入口与界面交互
```

### 工具类

| 类名 | 功能 |
|------|------|
| FileHelper | 文件读写与存在性校验 |
| StringHelper | 字符串分割、修剪、转大写 |

## 默认账户

| 项目 | 值 |
|------|-----|
| 用户名 | admin |
| 密码 | admin123 |
| 角色 | 管理员 (MANAGER) |

## 注意事项

1. **系统兼容性**：本系统仅支持 Windows 操作系统
2. **日期格式**：统一使用 `YYYY-MM-DD` 格式，非该格式的日期会被判定为无效
3. **数据安全**：数据以纯文本格式存储，请勿手动修改文件格式
4. **密码安全**：密码为明文存储，生产环境建议增加加密逻辑
5. **工作时长**：工作时长计算为简化版（按天计算，每天默认 8 小时）

## 项目协议

本项目遵循开源协议，欢迎学习和交流使用。
