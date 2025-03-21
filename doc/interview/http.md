# GET POST PUT DELETE在底层方面的区别
## 缓存
GET请求会缓存在浏览器缓存中，其他请求则不会缓存
## 参数
GET请求将参数拼接在url中，其他请求会将数据放在请求体中，依据restful规则，POST PUT DELETE的参数不应该放在url中进行拼接，保证安全性和幂等性。
## 幂等性
幂等性：多次发送同一个请求，返回的结果是相同的。
GET PUT DELETE请求都是幂等的， POST是非幂等的
## 作用
GET：用于数据的查询
POST：用于数据的创建
PUT：用于数据的更新
DELETE：用于数据的删除
