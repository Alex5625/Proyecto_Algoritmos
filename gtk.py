import gi
import csv

gi.require_version('Gtk', '4.0')
from gi.repository import Gtk, Gio, GObject, GdkPixbuf

APPID = 'com.fabio.duran.liststore'


class Row(GObject.Object):
    def __init__(self, *data):
        super().__init__()
        self.data = data


class Gtk4TestTest(Gtk.ApplicationWindow):
    def __init__(self, app):
        super().__init__(application=app, title='Visualización Alineación')
        self.set_default_size(400,300)

        # Leer matriz desde archivo CSV
        self.matriz = self.leer_csv('matriz_gtk.csv')
        if not self.matriz:
            print("El archivo CSV está vacío o no se pudo leer.")
            self.matriz = [["No hay datos"]]

        # Crear modelo Gio.ListStore
        self.model = Gio.ListStore()
        for fila in self.matriz:
            self.model.append(Row(*fila))

        # Crear HeaderBar
        header_bar = Gtk.HeaderBar.new()
        self.set_titlebar(header_bar)
        self.set_title("Visualización de Alineación")


        # Crear ColumnView
        smodel = Gtk.SingleSelection(model=self.model)
        smodel.connect("selection-changed", self.on_selected_items_changed)

        self.columnview = Gtk.ColumnView()
        self.columnview.set_model(smodel)

        # Crear columnas dinámicamente
        for i, _ in enumerate(self.matriz[0]):
            factory = Gtk.SignalListItemFactory()
            factory.connect("setup", self.on_list_item_setup)
            factory.connect("bind", self.on_list_item_bind, i)

            column = Gtk.ColumnViewColumn(title=f"Columna {i + 1}", factory=factory)
            column.set_resizable(True)
            column.set_expand(True)
            self.columnview.append_column(column)

        #Crear area para mostrar la imagen

        self.imagen = Gtk.Image()
        self.cargar_imagen("imagen.png")


        # Añadir ColumnView a la ventana

        box = Gtk.Box(orientation=Gtk.Orientation.VERTICAL)
        box.append(self.columnview)
        box.append(self.imagen)

        self.set_child(box)

    def leer_csv(self, nombreArchivo):
        matriz = []
        try:
            with open(nombreArchivo, newline='') as archivo_csv:
                lector_csv = csv.reader(archivo_csv)
                for fila in lector_csv:
                    matriz.append(fila)
        except FileNotFoundError:
            print(f"Error: El archivo {nombreArchivo} no se encontró.")
        except Exception as e:
            print(f"Error al leer el archivo: {e}")
        return matriz

    def cargar_imagen(self, image_path):
        pixbuf = GdkPixbuf.Pixbuf.new_from_file(image_path)
        scaled_pixbuf = pixbuf.scale_simple(200, 200, GdkPixbuf.InterpType.BILINEAR)
        self.imagen.set_from_pixbuf(scaled_pixbuf)

    def on_list_item_setup(self, factory, item):
        label = Gtk.Inscription()
        item.set_child(label)

    def on_list_item_bind(self, factory, item, columna_index):
        row = item.get_item()
        item.get_child().set_text(str(row.data[columna_index]))

    def on_clicked_save_list(self, widget):
        print("Funcionalidad de guardar pendiente.")

    def on_clicked_clean_list(self, widget):
        self.model.remove_all()
        print("Lista limpiada.")

    def on_selected_items_changed(self, selection, position, n_items):
        selected_item = selection.get_selected_item()
        if selected_item is not None:
            print(f"Seleccionado: {selected_item.data}")


class Gtk4TestApp(Gtk.Application):
    def __init__(self):
        super().__init__(application_id=APPID)

    def do_activate(self):
        window = Gtk4TestTest(self)
        window.present()


def main():
    app = Gtk4TestApp()
    app.run()


if __name__ == '__main__':
    main()
