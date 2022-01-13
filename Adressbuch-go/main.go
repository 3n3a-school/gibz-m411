package main

import (
//   "gorm.io/gorm"
//   "gorm.io/driver/sqlite"
//   "os"
  "fmt"
  "strings"
  "github.com/manifoldco/promptui"
)

// type Product struct {
//   gorm.Model
//   Code  string
//   Price uint
// }

type contact struct {
	Name	string
	Address string
	Phone	string
}

// func main() {

//   db, err := gorm.Open(sqlite.Open("test.db"), &gorm.Config{})
//   if err != nil {
//     panic("failed to connect database")
//   }

//   // Migrate the schema
//   db.AutoMigrate(&Product{})

//   // Create
//   db.Create(&Product{Code: "D42", Price: 100})

//   // Read
//   var product Product
//   db.First(&product, 1) // find product with integer primary key
//   db.First(&product, "code = ?", "D42") // find product with code D42

//   // Update - update product's price to 200
//   db.Model(&product).Update("Price", 200)
//   // Update - update multiple fields
//   db.Model(&product).Updates(Product{Price: 200, Code: "F42"}) // non-zero fields
//   db.Model(&product).Updates(map[string]interface{}{"Price": 200, "Code": "F42"})

//   // Delete - delete product
//   db.Delete(&product, 1)
// }

func executor(option int, menuoptions []string, contacts **[]contact) {
	switch option {
	case 0:
		add_contact(&**contacts)
		return;
	case 1:
		break;
	case 2:
		contact_prompt(&**contacts)
		return;
	default:
		fmt.Println("Bye...")
		break
	}
}



func prompt(options []string, contacts *[]contact) {
	prompt := promptui.Select{
		Label: "",
		Items: options,
	}

	i, _, err := prompt.Run()

	if err != nil {
		fmt.Printf("Prompt failed %v\n", err)
		return
	}

	executor(i, options, &contacts)
}

func contact_prompt(contacts *[]contact) {
	templates := &promptui.SelectTemplates{
		Label:    "{{ . }}?",
		Active:   "\U0001F914 {{ .Name | cyan }}",
		Inactive: "  {{ .Name | cyan }}",
		Selected: "\U0001F449 {{ .Name | green | cyan }}",
		Details: `
--------- Contacts ----------
{{ "Name:" | faint }}	{{ .Name }}
{{ "Address:" | faint }}	{{ .Address }}
{{ "Phonenumber:" | faint }}	{{ .Phone }}`,
	}

	searcher := func(input string, index int) bool {
		contact := (*contacts)[index]
		name := strings.Replace(strings.ToLower(contact.Name), " ", "", -1)
		input = strings.Replace(strings.ToLower(input), " ", "", -1)

		return strings.Contains(name, input)
	}

	prompt := promptui.Select{
		Label:     "Contacts Managment",
		Items:     *contacts,
		Templates: templates,
		Size:      4,
		Searcher:  searcher,
	}

	i, _, err := prompt.Run()

	if err != nil {
		fmt.Printf("Prompt failed %v\n", err)
		return
	}

	fmt.Printf("You chose number %d: %s\n", i+1, (*contacts)[i].Name)
}

func add_contact(contacts *[]contact) {
	questions := []string{"Name", "Address", "Phone"}
	prompt := promptui.Prompt{
		Label: "",
	}
	newcont := []string{}
	for _, q := range questions {
		prompt.Label = "Enter the "+q
		result, err := prompt.Run()
		
		if err != nil {
			fmt.Printf("Prompt failed %v\n", err)
			return
		}
		
		newcont = append(newcont, result)
	}
	
	newc := contact{newcont[0], newcont[1], newcont[2]}
	*contacts = append(*contacts, newc)
	return
}

func main() {
	menuoptions := []string{"Add Contact", "Delete Contact", "Modify Contact", "List All Contacts", "Search Contact"}
	contacts := []contact{
		{Name: "Bell Pepper", Address: "street 1", Phone: "123"},
	}
	for true {
		prompt(menuoptions, &contacts)
	}
}