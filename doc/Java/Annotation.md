
# 注解
## 元注解
定义注解的注解，基本注解
- @Retention：定义注解保留策略，定义注解在什么时候存在（源码阶段、编译后、运行时）
    - RetentionPolicy.SOURCE：注解仅保留在源码中，不会出现在class文件中
    - RetentionPolicy.CLASS：保留在源码和class中，但是运行时不存在
    - RetentionPolicy.RUNTIME：保留在运行时，可以通过反射机制获取
- @Target：描述自定义注解的使用范围
- @Inherited：是否可以被标注类的子类继承
- @Documented：是否在生成JavaDoc文档中体现
- @Repeatable：是否可以重复标注
- @Interface：声明注解类的关键字，使用该注解表示自动集成java.lang.annotation.Annotation类，定义注解的时候不能集成其他注解或者接口

## 注解的属性
注解的属性也叫做成员变量，注解只有成员变量没有方法，定义为无形参的方法，方法定义了成员变量的名字。

## 自定义注解
```java
public @interface MyAnnotation{
    String value();
}

@MyAnnotation("test")
public class MyClass{

}
```

## 注解处理器
java中的注解处理器类主要是AnnotatedElement接口的实现类，位于java.lang.reflect包下面
- isAnnotationPresent()：检查指定类型的注解是否存在于某个类
上，存在则返回true，否则返回false
- getAnnotation()：返回元素上存在的所有注解
- getFields()：获取某个类的public字段，包括父类的public字段
- getDeclaredFields()：获取哦某个类自身的所有字段，不包含父类
- setAccessible(true)：设置某个私有成员变量的属性值可操作
使用反射获取
通过反射方法和注解处理方法，可以获取到注解的内容，再进行其他处理，自定义注解是在特定的类中进行处理的。
