import { NgModule } from '@angular/core';
import { CommonModule } from '@angular/common';


import { MapRoutingModule } from './map-routing.module';
import { MapHomeComponent } from './map-home/map-home.component';
import { InfoListComponent } from './info-list/info-list.component';
import { SearchBarComponent } from './search-bar/search-bar.component';
import { MapUiComponent } from './map-ui/map-ui.component';


@NgModule({
  declarations: [
    MapHomeComponent,
    InfoListComponent,
    SearchBarComponent,
    MapUiComponent
  ],
  imports: [
    CommonModule,
    MapRoutingModule
  ]
})
export class MapModule { }
