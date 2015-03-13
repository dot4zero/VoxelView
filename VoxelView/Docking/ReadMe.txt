SLN 22.03.20012
Инструкция по работе с докпанелью.

1) SafeDockPanel является расширением класса DockPanel: 
   сохраняет не только расположение доков, но их содержимое,
   реализует интерфейс IStorable.

   SafeDockContent является расширением класса DockContent:
   формирует PersistString как <тип дока>/<аргументы>,
   реализует интерфейс IStorable,
   работает свойство ShowIcon - показывать значок дока или нет (теперь не надо ставить доку empty.ico!!!)

2) Важно: Контролы, которые будут показываться на докпанели, 
должны быть наследниками SafeDockContent! Например:
	class MyControl : SafeDockContent
	{
		public MyControl()
		{
			InitializeComponent();
			this.DockAreas = DockingAreas.Tools;
			this.ShowHint = DockingState.Left;
			this.TabText = "Свойства";
			this.Image = Images.GetImage(ImageKey.Свойства);
		}
		public override void SaveXml(XmlElement xmlParent) {...}
		public override void LoadXml(XmlElement xmlParent) {...}
		
		//Если доку требуется отложенное обновление, т.е. обновлять только тогда, когда он видим
		//и не обновлять, если он не видим, перекройте этот метод:
		protected override void UpdateContentAlways() {...}
		//Чтобы обновить содержимое дока, вызывайте метод UpdateContent()
	}
	
Примечание. По умолчанию
	СloseButton = true; //Кнопка Закрыть доступна
	СloseButtonVisible = true; //Кнопка Закрыть видима
	HideOnClose = false; //Разрушать на закрытие
	DockAreas = DockingAreas.Anywhere; //Можно парковать везде, где угодно - Document+Float+Top+Bottom+Left+Right
	ShowHint = DockingState.Document; //Первоначальная парковка - документ
	ShowIcon = true; //Показывать значок дока
	
Примечание. Старое объявление контрола как class MyControl: UserControl, IStorable, ISupportDelayedUpdate
меняем на class MyControl: SafeDockContent.

3) Создание докпанели на форме или на каком-то контроле:
	_dockPanel = new SafeDockPanel{Parent = this, DocumentStyle = DockingStyle.Sdi};
Примечание. По умолчанию
	DocumentStyle = DockingStyle.Window
	
4) Регистрация делегатов содания доков (для автоматического их восстановления из xml):
	_dockPanel[typeof(MyControl)] = (args) => new MyControl();
или
	MyControl _myControl = new MyControl();
	...
	_dockPanel[typeof(MyControl)] = (args) => _myControl;
	
	Во втором случае требуется
	либо запретить закрывать док: СloseButton = false; (или СloseButtonVisible = false;)
	либо прятать его на закрытии, а не разрушать: HideOnClose = true;
	либо подписаться на Disposed и оборвать корни: _myControl.Disposed += (sender, e) => _myControl = null;

3) Показать док (если такого дока нет, то он будет создан):
	_dockPanel.ShowDock<MyControl>(args);
или
	_dockPanel.ShowDock<MyControl>();
или
	_dockPanel.ShowDock(_myControl);
	
4) Получить док на локальную переменную:
	var tmp = _dockPanel.GetDock<MyControl>();
или
	var tmp = _dockPanel.GetDock<MyControl>(args);

5) Сохранение/восстановление докпанели (вместе с доками и их содержимым):
	_dockPanel.SaveXml(xmlParent);
	_dockPanel.LoadXml(xmlParent);
