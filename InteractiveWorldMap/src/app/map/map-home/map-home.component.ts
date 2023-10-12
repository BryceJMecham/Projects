import { Component, Injectable } from '@angular/core';
import { MapserviceService } from '../../mapservice.service'

import { MapModule } from '../map.module';

@Component({
  selector: 'app-map-home',
  templateUrl: './map-home.component.html',
  styleUrls: ['./map-home.component.css']
})
export class MapHomeComponent {
  info: any;
  countryName: any;
  capital: any;
  region: any;
  income: any;
  continentName: any;
  population: any;
  errorMsg?: any;
  incomeInfo: any;

  constructor(private mapservice: MapserviceService){}

  onTerm(term: string){
    this.countryName = "Loading...";
    this.capital = "Loading...";
    this.region = "Loading...";
    this.income = "Loading...";
    this.continentName = "Loading...";
    this.population = "Loading...";
  
    this.mapservice.search().subscribe((response: any) =>{
      this.info = response;
      this.countryName = term;
      this.capital = '';

      this.continentName = '';
      this.population = '';
      this.errorMsg = '';

      for(let x=0; x<this.info.geonames.length; x++){

        if(this.info.geonames[x].countryName == this.countryName){
          this.capital = this.info.geonames[x].capital;

          this.continentName = this.info.geonames[x].continentName;
          this.population = this.info.geonames[x].population;
          if(this.region == 'Loading...'){
            this.region = "No Regional Data Found"
          }
          if(this.income == 'Loading...'){
            this.income = "No Income Data Found"
          }
        }
      }
      if(this.capital == ''){
        this.capital = "No capital data found"
      }
      if(this.continentName == ''){
        this.errorMsg = "Could not find the country. Please make sure the country name is spelled correctly and first letters are capitlaized. "; 
        this.capital = '';
        this.region = '';
        this.income = '';
      }
      
    });
    this.mapservice.lowSearch().subscribe((response: any) =>{
      this.incomeInfo = response;
      this.countryName = term;

      this.region = '';
      this.income = '';

      for(let x=0; x<this.incomeInfo[1].length; x++){
        if(this.incomeInfo[1][x].name == this.countryName){
          this.region = this.incomeInfo[1][x].region.value;
          this.income = this.incomeInfo[1][x].incomeLevel.value;
        }
      }
      if(this.region == ''){
        
        this.mapservice.middleSearch().subscribe((response: any) =>{
          this.incomeInfo = response;
          this.countryName = term;
    
          this.region = '';
          this.income = '';
    
          for(let y=0; y<this.incomeInfo[1].length; y++){
            if(this.incomeInfo[1][y].name == this.countryName){
              this.region = this.incomeInfo[1][y].region.value;
              this.income = this.incomeInfo[1][y].incomeLevel.value;
            }
          }
          if(this.region == ''){
            
            this.mapservice.highSearch().subscribe((response: any) =>{
              this.incomeInfo = response;
              this.countryName = term;
        
              this.region = '';
              this.income = '';
        
              for(let x=0; x<this.incomeInfo[1].length; x++){
                if(this.incomeInfo[1][x].name == this.countryName){
                  this.region = this.incomeInfo[1][x].region.value;
                  this.income = this.incomeInfo[1][x].incomeLevel.value;
                }
              }
              if(this.region == ''){
                this.region = 'Loading...';
                this.income = 'Loading...';
              }


            });
    
          }
        });

      }

    });
    
  }
}
